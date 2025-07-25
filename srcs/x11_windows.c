/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_windows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:36:34 by reclaire          #+#    #+#             */
/*   Updated: 2025/07/08 03:09:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _FT_RETURN

#include "libftGFX_x11.h"

#include "libft/std.h"
#include "libft/limits.h"

#if FT_OS_LINUX

void ftgfxx11_window_reset(struct s_ftGFX_window *window)
{
	for (U16 i = 0; i < sizeof(window->keys) / sizeof(window->keys[0]); i++)
	{
		if (window->keys[i] == FTGFX_KEY_STATE_PRESSED)
			window->keys[i] = FTGFX_KEY_STATE_DOWN;
		else if (window->keys[i] == FTGFX_KEY_STATE_RELEASED)
			window->keys[i] = FTGFX_KEY_STATE_UP;
	}

	for (U8 i = 0; i < sizeof(window->mouse) / sizeof(window->mouse[0]); i++)
	{
		if (window->mouse[i] == FTGFX_MOUSE_STATE_PRESSED)
			window->mouse[i] = FTGFX_MOUSE_STATE_DOWN;
		else if (window->mouse[i] == FTGFX_MOUSE_STATE_RELEASED)
			window->mouse[i] = FTGFX_MOUSE_STATE_UP;
	}

	window->mouse_delta = ivec2_zero;
	window->damage = ivec4_zero;
}

static bool init_buffer(struct s_ftGFX_ctx *ctx, struct s_framebuffer *buffer, t_iv2 size)
{
	struct s_ftGFX_ctx_private *private;

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	{ /* Init everything to 0 to be able to jump to exit_* labels. */
		buffer->img.data = NULL;
		buffer->ximage = NULL;
		buffer->xpixmap = None;
	}

	{ /* Libft image. */
		if (!ft_init_image(&buffer->img, size))
			goto _exit_err; /* ft_errno set by ft_init_image */

		// TODO: switch back to bzero once I make it faster than ft_fill_rect
		ft_fill_rect(&buffer->img, ft_image_rect(&buffer->img), ft_color(0), 0);
		// ft_bzero(buffer->img.data, sizeof(t_color) * size.x * size.y);
	}

	if ((buffer->ximage = XCreateImage(private->display, private->visual, private->depth, ZPixmap, 0,
									   (char *)buffer->img.data, size.x, size.y, 32, 0)) == NULL)
		goto exit_invop;

	if ((buffer->xpixmap = XCreatePixmap(private->display, private->root, size.x, size.y, private->depth)) == 0)
		goto exit_invop;

	buffer->format = ZPixmap;
	buffer->shm = FALSE;

	FT_RET_OK(TRUE);

exit_invop:
	ft_errno = FT_EINVOP;
	goto _exit_err;

_exit_err:
	if (buffer->img.data != NULL)
		ft_destroy_image(&buffer->img);
	if (buffer->ximage != NULL)
		XDestroyImage(buffer->ximage);
	if (buffer->xpixmap != None)
		XFreePixmap(private->display, buffer->xpixmap);
	return FALSE;
}

struct s_ftGFX_window *ftGFX_create_window(struct s_ftGFX_ctx *ctx, t_iv2 size, const_string title)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window *win;
	struct s_ftGFX_window_private *win_private;

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	{
		win = NULL;
		win_private = NULL;
	}

	if (UNLIKELY((win = malloc(sizeof(struct s_ftGFX_window) + sizeof(struct s_ftGFX_window_private))) == NULL))
		goto exit_omem;
	win_private = (struct s_ftGFX_window_private *)win->private;

	win->ctx = ctx;
	win->size = size;

	if ((win->name = ft_strdup(title)) == NULL)
		goto exit_omem;

	{ /* Init framebuffer */
		if (!init_buffer(ctx, &win_private->framebuffer, win->size))
			goto _exit_err; /* ft_errno already set by init_buffer */
		win->surface = &win_private->framebuffer.img;
	}

	{ /* Window creation */
		U64 win_valuemask;
		XSetWindowAttributes xswa;

		xswa = (XSetWindowAttributes){
			.background_pixel = 0,
			.border_pixel = -1,
			.colormap = private->cmap,
			.event_mask = 0 | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask | PointerMotionMask | ButtonMotionMask | ExposureMask,
		};
		win_valuemask = CWEventMask | CWBackPixel | CWBorderPixel | CWColormap;

		if ((win_private->window = XCreateWindow(private->display, private->root,
												 0, 0, size.x, size.y,
												 0, CopyFromParent, InputOutput, private->visual,
												 win_valuemask, &xswa)) == None)
			goto exit_invop;
	}

	{ /* Atoms */
		if (XStoreName(private->display, win_private->window, title) == 0)
			goto exit_invop;
		if (XSetWMProtocols(private->display, win_private->window, &(private->del_win_atom), 1) == 0)
			goto exit_invop;
	}

	{ /* No resize */
		XSizeHints hints;
		long dummy;

		XGetWMNormalHints(private->display, win_private->window, &hints, &dummy);
		hints.width = size.x;
		hints.height = size.y;
		hints.min_width = size.x;
		hints.min_height = size.y;
		hints.max_width = size.x;
		hints.max_height = size.y;
		hints.flags = PSize | PMinSize | PMaxSize;
		XSetWMNormalHints(private->display, win_private->window, &hints);
	}

	{ /* Graphics context */
		XGCValues xgcv;

		xgcv = (XGCValues){
			.foreground = -1,
			.function = GXcopy,
			.plane_mask = AllPlanes,
		};
		win_private->gc = XCreateGC(private->display, win_private->window, GCFunction | GCPlaneMask | GCForeground, &xgcv);
	}

	/* Put on top */
	ftGFX_bring_top(win);

	{ /* Wait first exposure */
		XEvent ev;
		XWindowEvent(private->display, win_private->window, ExposureMask, &ev);
		XPutBackEvent(private->display, &ev);
	}

	win->next = ctx->windows;
	ctx->windows = win;

	win->should_close = FALSE;

	ft_bzero(win->keys, sizeof(win->keys));
	ft_bzero(win->mouse, sizeof(win->mouse));
	win->mouse_delta = ivec2_zero;
	win_private->last_mouse_pos = ftGFX_mouse_get_pos(ctx, win);

	win_private->cursor_hidden = FALSE;
	win_private->cursor_current = FTGFX_CURSOR_DEFAULT;

	win->damage = ivec4_zero;

	return win;

exit_omem:
	ft_errno = FT_EOMEM;
	goto _exit_err;

exit_invop:
	ft_errno = FT_EINVOP;
	goto _exit_err;

_exit_err:
	if (win)
	{
		// TODO:
		free(win->name);
		free(win);
	}
	return NULL;
}

void ftGFX_destroy_window(struct s_ftGFX_window *win)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;
	struct s_ftGFX_window *prev;
	struct s_ftGFX_window *lst;

	private = (struct s_ftGFX_ctx_private *)win->ctx->private;
	win_private = (struct s_ftGFX_window_private *)win->private;

	if (win == win->ctx->windows)
		win->ctx->windows = win->next;
	else
	{
		prev = win->ctx->windows;
		lst = win->ctx->windows->next;
		while (lst)
		{
			if (lst == win)
				break;
			prev = lst;
			lst = lst->next;
		}

		if (lst != NULL)
			prev->next = lst->next;
	}

	free(win->name);
	XFreeGC(private->display, win_private->gc);
	XDestroyWindow(private->display, win_private->window);
	XDestroyImage(win_private->framebuffer.ximage);
	free(win);
}

void ftGFX_bring_top(struct s_ftGFX_window *win)
{
	struct s_ftGFX_window_private *win_private;

	win_private = (struct s_ftGFX_window_private *)win->private;
	XMapRaised(((struct s_ftGFX_ctx_private *)win->ctx->private)->display, win_private->window);
}

void ftGFX_set_win_name(struct s_ftGFX_window *win, string name)
{
	struct s_ftGFX_window_private *win_private;

	win_private = (struct s_ftGFX_window_private *)win->private;

	LIMIT_FREQ(1);
	free(win->name);
	win->name = ft_strdup(name);
	XStoreName(((struct s_ftGFX_ctx_private *)win->ctx->private)->display, win_private->window, name);
}

void ftGFX_set_win_name_infos(struct s_ftGFX_window *win, string infos)
{
	struct s_ftGFX_window_private *win_private;

	win_private = (struct s_ftGFX_window_private *)win->private;

	LIMIT_FREQ(0.15);
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "%s - %s", win->name, infos);
	XStoreName(((struct s_ftGFX_ctx_private *)win->ctx->private)->display, win_private->window, buffer);
}

void ftGFX_move_window(struct s_ftGFX_window *win, t_iv2 pos)
{
	struct s_ftGFX_window_private *win_private;

	win_private = (struct s_ftGFX_window_private *)win->private;
	XMoveWindow(((struct s_ftGFX_ctx_private *)win->ctx->private)->display, win_private->window, pos.x, pos.y);
}

void ftGFX_clear_window(struct s_ftGFX_window *win)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	private = (struct s_ftGFX_ctx_private *)win->ctx->private;
	win_private = (struct s_ftGFX_window_private *)win->private;

	XClearWindow(private->display, win_private->window);
	if (private->flush)
		XFlush(private->display);
}

void ftGFX_blt_screen(struct s_ftGFX_window *win)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	private = (struct s_ftGFX_ctx_private *)win->ctx->private;
	win_private = (struct s_ftGFX_window_private *)win->private;

	XSetClipOrigin(private->display, win_private->gc, 0, 0);

	if (win_private->framebuffer.shm)
	{
		ft_printf("%s:%d TODO\n", __FILE__, __LINE__);
	}
	else
	{
		XPutImage(private->display,
				  win_private->framebuffer.xpixmap,
				  win_private->gc,
				  win_private->framebuffer.ximage, 0, 0, 0, 0,
				  win->size.x, win->size.y);
	}

	XCopyArea(private->display,
			  win_private->framebuffer.xpixmap,
			  win_private->window,
			  win_private->gc,
			  0, 0,
			  win->size.x, win->size.y,
			  0, 0);
	if (private->flush)
		XFlush(private->display);
}

#endif
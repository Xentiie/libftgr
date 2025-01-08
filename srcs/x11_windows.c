/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_windows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:36:34 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/27 00:39:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_x11_int.h"
#include "libft/limits.h"

#ifdef FT_OS_LINUX

static inline bool _init_buffer(t_ftgr_ctx *ctx, t_framebuffer_data *buffer, t_iv2 size)
{
	buffer->img.bpp = 4;
	buffer->img.size = size;
	buffer->img.line_size = size.x * 4;
	buffer->img.data_size = buffer->img.line_size * size.y;
	buffer->img.data = malloc(sizeof(U8) * buffer->img.data_size);
	if (UNLIKELY(buffer->img.data == NULL))
		return FALSE;
	buffer->img.pixels = (t_color *)buffer->img.data;
	ft_memset(buffer->img.data, 255, buffer->img.data_size);

	buffer->ximage = XCreateImage(ctx->display, ctx->visual, ctx->depth, ZPixmap, 0,
								  (char *)buffer->img.data, size.x, size.y, 32, 0);
	buffer->pixmap = XCreatePixmap(ctx->display, ctx->root, size.x, size.y, ctx->depth);
	// TODO: check return code
	buffer->format = ZPixmap;
	buffer->shm = FALSE;
	buffer->gc = 0;

	return TRUE;
}

t_ftgr_win *ftgr_new_window(t_ftgr_ctx *ctx, t_iv2 size, const_string title)
{
	t_ftgr_win *win = NULL;
	t_ftgr_win_int *win_int = NULL;

	if (UNLIKELY((win = malloc(sizeof(t_ftgr_win))) == NULL) ||
		UNLIKELY((win_int = malloc(sizeof(t_ftgr_win_int))) == NULL))
	{
		free(win);
		return NULL;
	}
	ft_memset(win, 0, sizeof(t_ftgr_win));
	ft_memset(win_int, 0, sizeof(t_ftgr_win_int));

	win->size = size;
	win->ctx = ctx;
	win->internal = win_int;

	{ // Window creation
		XSetWindowAttributes xswa = (XSetWindowAttributes){
			.background_pixel = 0,
			.border_pixel = -1,
			.colormap = ctx->cmap,
			.event_mask = 0xFFFFFF};
		U64 win_valuemask = CWEventMask | CWBackPixel | CWBorderPixel | CWColormap;

		win_int->window = XCreateWindow(ctx->display, ctx->root,
										0, 0, size.x, size.y,
										0, CopyFromParent, InputOutput, ctx->visual,
										win_valuemask, &xswa);
	}

	{ // Atoms
		XStoreName(ctx->display, win_int->window, title);
		XSetWMProtocols(ctx->display, win_int->window, &(ctx->del_win_atom), 1);
	}

	{ // No resize
		XSizeHints hints;
		long dummy;

		XGetWMNormalHints(ctx->display, win_int->window, &hints, &dummy);
		hints.width = size.x;
		hints.height = size.y;
		hints.min_width = size.x;
		hints.min_height = size.y;
		hints.max_width = size.x;
		hints.max_height = size.y;
		hints.flags = PPosition | PSize | PMinSize | PMaxSize;
		XSetWMNormalHints(ctx->display, win_int->window, &hints);
	}

	{ // Graphics context
		XGCValues xgcv = (XGCValues){
			.foreground = -1,
			.function = GXcopy,
			.plane_mask = AllPlanes};
		win_int->gc = XCreateGC(ctx->display, win_int->window, GCFunction | GCPlaneMask | GCForeground, &xgcv);
	}

	// Put on top
	ftgr_bring_top(win);

	{ // Wait first exposure
		XEvent ev;
		XWindowEvent(ctx->display, win_int->window, ExposureMask, &ev);
		XPutBackEvent(ctx->display, &ev);
	}

	t_list *lst = ft_lstnew(win);
	ft_lstadd_front(&ctx->windows, lst);

	{ // Init front/back framebuffers
		_init_buffer(ctx, &win_int->buffers[0], win->size);
		_init_buffer(ctx, &win_int->buffers[1], win->size);
		// TODO: check error

		win_int->front = 0;
		win_int->back = 1;
		win->surface = &(win_int->buffers[win_int->back].img);
		ft_bzero(win->surface->data, win->surface->data_size);
		ftgr_swap_buffers(win);
		ft_bzero(win->surface->data, win->surface->data_size);
		ftgr_swap_buffers(win);
	}

	win->name = ft_strdup(title);

	win->w_root = ftgr_new_widget();
	win->w_root->size = size;

	win->damage = ivec4(S32_MAX, S32_MAX, S32_MIN, S32_MIN);

	win->events_n = 0;
	win->events_alloc = 8;
	if (UNLIKELY((win->events = malloc(sizeof(t_ftgr_ev) * win->events_alloc)) == NULL))
	{
		return NULL;
	}

	return win;
}

bool _ftgr_add_event(t_ftgr_win *win, t_ftgr_ev ev)
{
	t_ftgr_ev *new;

	if (win->events_n >= win->events_alloc)
	{
		if (UNLIKELY((new = malloc(sizeof(t_ftgr_ev *) * win->events_n * 2)) == NULL))
			FT_RET_ERR(FALSE, FT_EOMEM);
		ft_memcpy(new, win->events, sizeof(t_ftgr_ev *) * win->events_n);
		free(win->events);
		win->events = new;
		win->events_alloc = win->events_n * 2;
	}

	win->events[win->events_n++] = ev;
	FT_RET_OK(TRUE);
}

static bool cmp_window(void *a1, void *a2)
{
	return a1 == a2;
}
void ftgr_free_window(t_ftgr_win *win)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	free(win->name);
	XFreeGC(win->ctx->display, win_int->gc);
	XDestroyWindow(win->ctx->display, win_int->window);
	ft_lstremoveif(&win->ctx->windows, NULL, cmp_window, win);
	free(win);
}

void ftgr_bring_top(t_ftgr_win *win)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);
	XMapRaised(win->ctx->display, win_int->window);
}

void ftgr_set_win_name(t_ftgr_win *win, string name)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	LIMIT_FREQ(1);
	free(win->name);
	win->name = ft_strdup(name);
	XStoreName(win->ctx->display, win_int->window, name);
}

void ftgr_set_win_name_infos(t_ftgr_win *win, string infos)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	LIMIT_FREQ(1);
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "%s - %s", win->name, infos);
	XStoreName(win->ctx->display, win_int->window, buffer);
}

void ftgr_move_window(t_ftgr_win *win, t_iv2 pos)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);
	XMoveWindow(win->ctx->display, win_int->window, pos.x, pos.y);
}

void ftgr_clear_window(t_ftgr_ctx *xvar, t_ftgr_win *win)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	XClearWindow(xvar->display, win_int->window);
	if (xvar->flush)
		XFlush(xvar->display);
}

void ftgr_blt_screen(t_ftgr_win *win)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	GC gc = win_int->gc;
	if (win_int->gc)
	{
		gc = win_int->gc;
		XSetClipOrigin(win->ctx->display, gc, 0, 0);
	}

	t_framebuffer_data fb = win_int->buffers[win_int->back];

	if (fb.shm)
	{
	}
	else
	{
		XPutImage(win->ctx->display, fb.pixmap, win_int->gc, fb.ximage, 0, 0, 0, 0,
				  win->size.x, win->size.y);
	}

	XCopyArea(win->ctx->display, fb.pixmap, win_int->window, gc,
			  0, 0, win->size.x, win->size.y, 0, 0);
	if (win->ctx->flush)
		XFlush(win->ctx->display);
}

void ftgr_swap_buffers(t_ftgr_win *win)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	ftgr_blt_screen(win);

	win_int->front = !win_int->front;
	win_int->back = !win_int->back;
	win->surface = &win_int->buffers[win_int->back].img;
}

#endif
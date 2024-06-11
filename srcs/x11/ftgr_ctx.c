/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:46:04 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/09 15:56:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"
#include "libft/time.h"
#include <unistd.h>

static void	ftgr_init_shm(t_ftgr_ctx *ctx);
//TODO: check return codes

static int error_handler(Display *display, XErrorEvent *event)
{
	printf("X11 ERROR: (%u:%u) req:%u resoureid:%d serial:%lu type:%d\n", event->error_code, event->minor_code, event->request_code, event->resourceid, event->serial, event->type);
}

t_ftgr_ctx	*ftgr_create_ctx()
{
	t_ftgr_ctx *ctx;

	ctx = malloc(sizeof(t_ftgr_ctx));
	if (!ctx)
		__FTRETURN_ERR(NULL, FT_EOMEM);

	ctx->display = XOpenDisplay("");
	if (ctx->display == 0)
	{
		free(ctx);
		__FTRETURN_ERR(NULL, FTGR_EX11);
	}

	XSetErrorHandler(error_handler);

	ctx->screen = DefaultScreen(ctx->display);
	ctx->root = DefaultRootWindow(ctx->display);
	ctx->cmap = DefaultColormap(ctx->display, ctx->screen);
	ctx->depth = DefaultDepth(ctx->display, ctx->screen);

	ctx->visual = DefaultVisual(ctx->display, ctx->screen);
	if (ctx->visual->class != TrueColor)
	{
		S32 nb_item;
		XVisualInfo template = (XVisualInfo){.class = TrueColor, .depth = ctx->depth};

		XVisualInfo *vi = XGetVisualInfo(ctx->display, VisualDepthMask | VisualClassMask, &template, &nb_item);
		if (!vi)
		{
			// TODO: CLEANUP
			// No truecolor
			XCloseDisplay(ctx->display);
			free(ctx);
			__FTRETURN_ERR(NULL, FTGR_EX11);
		}

		ctx->visual = vi->visual;
		ctx->cmap = XCreateColormap(ctx->display, ctx->root, ctx->visual, AllocNone);
	}


	ctx->flush = TRUE;
	ctx->windows = NULL;

	ctx->del_win_atom = XInternAtom(ctx->display, "WM_DELETE_WINDOW", False);
	ctx->protocols_atom = XInternAtom(ctx->display, "WM_PROTOCOLS", False);

	ftgr_init_shm(ctx);
	//ftgr_int_rgb_conversion(ctx);

	clk_get(&ctx->global_time);
	clk_get(&ctx->delta_time_clk);

	ctx->keys = NULL;
	return (ctx);
}

static void	ftgr_init_shm(t_ftgr_ctx *ctx)
{
	S32 dummy;

	S32		use_pshm;
	char	*dpy;
	char	hostname[33];

	ctx->use_xshm = XShmQueryVersion(ctx->display, &dummy, &dummy, &use_pshm);

	if (ctx->use_xshm && use_pshm)
		ctx->pixmap_shm_format = XShmPixmapFormat(ctx->display);
	else
		ctx->pixmap_shm_format = -1;

	gethostname(hostname, 32);
	
	dpy = getenv("DISPLAY");
	if (dpy && ft_strlen(dpy) && *dpy != ':' && ft_strncmp(dpy, hostname, ft_strlen(hostname)) &&
			ft_strncmp(dpy, LOCALHOST, ft_strlen(LOCALHOST)))
	{
		ctx->pixmap_shm_format = -1;
		ctx->use_xshm = FALSE;
	}

	ctx->windows = NULL;
	if (!ctx->use_xshm)
		fprintf(stderr, "Warning: not using shared memory\n");
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx11_ctx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:46:04 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/10 10:55:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftx11_int.h"
#include <unistd.h>

static void	ftx11_init_shm(t_ftx11_ctx *ctx);

//TODO: check return codes

t_ftx11_ctx	*ftx11_create_ctx()
{
	t_ftx11_ctx *ctx;

	ctx = malloc(sizeof(t_ftx11_ctx));
	if (!ctx)
		return NULL;

	ctx->display = XOpenDisplay("");
	if (ctx->display == 0)
	{
		// TODO: CLEANUP
		return NULL;
	}

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
			return NULL;
		}

		ctx->visual = vi->visual;
		ctx->cmap = XCreateColormap(ctx->display, ctx->root, ctx->visual, AllocNone);
	}

	ctx->screen = DefaultScreen(ctx->display);
	ctx->root = DefaultRootWindow(ctx->display);
	ctx->cmap = DefaultColormap(ctx->display, ctx->screen);
	ctx->depth = DefaultDepth(ctx->display, ctx->screen);

	ctx->flush = TRUE;
	ctx->run = FALSE;

	ctx->loop_hooks = NULL;
	ctx->windows = NULL;

	ctx->del_win_atom = XInternAtom(ctx->display, "WM_DELETE_WINDOW", False);
	ctx->protocols_atom = XInternAtom(ctx->display, "WM_PROTOCOLS", False);

	ftx11_init_shm(ctx);
	//ftx11_int_rgb_conversion(ctx);

	return (ctx);
}

static void	ftx11_init_shm(t_ftx11_ctx *ctx)
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
}

/*

int ftx11_int_rgb_conversion(t_ftx11_ctx *ctx)
{
	bzero(ctx->decrgb, sizeof(int) * 6);
	while (!(ctx->visual->red_mask & 1))
	{
		ctx->visual->red_mask >>= 1;
		ctx->decrgb[0]++;
	}
	while (ctx->visual->red_mask & 1)
	{
		ctx->visual->red_mask >>= 1;
		ctx->decrgb[1]++;
	}
	while (!(ctx->visual->green_mask & 1))
	{
		ctx->visual->green_mask >>= 1;
		ctx->decrgb[2]++;
	}
	while (ctx->visual->green_mask & 1)
	{
		ctx->visual->green_mask >>= 1;
		ctx->decrgb[3]++;
	}
	while (!(ctx->visual->blue_mask & 1))
	{
		ctx->visual->blue_mask >>= 1;
		ctx->decrgb[4]++;
	}
	while (ctx->visual->blue_mask & 1)
	{
		ctx->visual->blue_mask >>= 1;
		ctx->decrgb[5]++;
	}
}

*/
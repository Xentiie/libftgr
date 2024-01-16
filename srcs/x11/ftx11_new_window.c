/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx11_new_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:26:49 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/09 23:26:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftx11_int.h"

t_ftx11_win *ftx11_new_window(t_ftx11_ctx *ctx, t_iv2 size, const_string title)
{
	t_ftx11_win *new_win = malloc(sizeof(t_ftx11_win));
	if (!new_win)
		return (NULL);

	XSetWindowAttributes xswa = (XSetWindowAttributes){
		.background_pixel = 0,
		.border_pixel = -1,
		.colormap = ctx->cmap,
		.event_mask = 0xFFFFFF};
	U64 win_valuemask = CWEventMask | CWBackPixel | CWBorderPixel | CWColormap;
	new_win->window = XCreateWindow(ctx->display, ctx->root,
									0, 0, size.x, size.y,
									0, CopyFromParent, InputOutput, ctx->visual,
									win_valuemask, &xswa);

	// Atoms
	XStoreName(ctx->display, new_win->window, title);
	XSetWMProtocols(ctx->display, new_win->window, &(ctx->del_win_atom), 1);
	// No resize
	XSizeHints hints;
	long dummy;
	XGetWMNormalHints(ctx->display, new_win->window, &hints, &dummy);
	hints.width = size.x;
	hints.height = size.y;
	hints.min_width = size.x;
	hints.min_height = size.y;
	hints.max_width = size.x;
	hints.max_height = size.y;
	hints.flags = PPosition | PSize | PMinSize | PMaxSize;
	XSetWMNormalHints(ctx->display, new_win->window, &hints);

	// Graphics context
	XGCValues xgcv = (XGCValues){
		.foreground = -1,
		.function = GXcopy,
		.plane_mask = AllPlanes};
	new_win->gc = XCreateGC(ctx->display, new_win->window, GCFunction | GCPlaneMask | GCForeground, &xgcv);

	// Put on top
	XMapRaised(ctx->display, new_win->window);

	// Wait first exposure
	XEvent ev;
	XWindowEvent(ctx->display, new_win->window, ExposureMask, &ev);
	XPutBackEvent(ctx->display, &ev);

	t_list *lst = ft_lstnew(new_win);
	ft_lstadd_front(&ctx->windows, lst);

	return new_win;
}

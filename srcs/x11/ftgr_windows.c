/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_windows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:36:34 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/08 22:55:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"

t_ftgr_win *ftgr_new_window(t_ftgr_ctx *ctx, t_iv2 size, const_string title)
{
	t_ftgr_win *new_win = malloc(sizeof(t_ftgr_win));
	if (!new_win)
		return (NULL);
	new_win->ctx = ctx;

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
	ftgr_bring_top(new_win);

	// Wait first exposure
	XEvent ev;
	XWindowEvent(ctx->display, new_win->window, ExposureMask, &ev);
	XPutBackEvent(ctx->display, &ev);

	t_list *lst = ft_lstnew(new_win);
	ft_lstadd_front(&ctx->windows, lst);

	new_win->name = ft_strdup(title);

	return new_win;
}


static bool cmp_window(void *a1, void *a2)
{return a1 == a2;}
void ftgr_free_window(t_ftgr_win *win)
{
	free(win->name);
	XFreeGC(win->ctx->display, win->gc);
	XDestroyWindow(win->ctx->display, win->window);
	ft_lstremoveif(&win->ctx->windows, NULL, cmp_window, win);
	free(win);
}

void ftgr_bring_top(t_ftgr_win *win)
{
	XMapRaised(win->ctx->display, win->window);
}

void ftgr_set_win_name(t_ftgr_win *win, string name)
{
	LIMIT_FREQ(1);
	free(win->name);
	win->name = ft_strdup(name);
	XStoreName(win->ctx->display, win->window, name);
}

void ftgr_set_win_name_infos(t_ftgr_win *win, string infos)
{
	LIMIT_FREQ(1);
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "%s - %s", win->name, infos);
	XStoreName(win->ctx->display, win->window, buffer);
}

void ftgr_move_window(t_ftgr_win *win, t_iv2 pos)
{
	XMoveWindow(win->ctx->display, win->window, pos.x, pos.y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:07:44 by reclaire          #+#    #+#             */
/*   Updated: 2024/04/16 23:40:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"

void ftgr_mouse_move(t_ftgr_ctx *ctx, t_ftgr_win *win, t_iv2 pos)
{
	XWarpPointer(ctx->display, None, win->window, 0, 0, 0, 0, pos.x, pos.y);
}

void ftgr_mouse_hide(t_ftgr_ctx *ctx, t_ftgr_win *win)
{
	static char data[1] = {0};
	Pixmap blank = XCreateBitmapFromData(ctx->display, win->window, data, 1, 1);
	
	XColor dummy;
	Cursor cursor = XCreatePixmapCursor(ctx->display, blank, blank, &dummy, &dummy, 0, 0);

	XDefineCursor(ctx->display, win->window, cursor);
	XFreePixmap(ctx->display, blank);
	XFreeCursor(ctx->display, cursor);
}

void ftgr_mouse_show(t_ftgr_ctx *ctx, t_ftgr_win *win)
{
	XUndefineCursor(ctx->display, win->window);
}

t_iv2 ftgr_mouse_get_pos(t_ftgr_ctx *ctx, t_ftgr_win *win)
{
	Window		root_return;
	Window		child_return;
	int				root_x_return;
	int				root_y_return;
	unsigned	mask_return;

	t_iv2			out;

	XQueryPointer(ctx->display, win->window,
		&root_return, &child_return, &root_x_return, &root_y_return,
		&out.x, &out.y, &mask_return);
	return out;
}

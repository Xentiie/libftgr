/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:07:44 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/01 13:13:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_x11_int.h"
#ifdef FT_OS_LINUX

void ftgr_mouse_move(t_ftgr_ctx *ctx, t_ftgr_win *win, t_iv2 pos)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	XWarpPointer(ctx->display, None, win_int->window, 0, 0, 0, 0, pos.x, pos.y);
}

void ftgr_mouse_hide(t_ftgr_ctx *ctx, t_ftgr_win *win)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	static char data[1] = {0};
	Pixmap blank = XCreateBitmapFromData(ctx->display, win_int->window, data, 1, 1);

	XColor dummy;
	Cursor cursor = XCreatePixmapCursor(ctx->display, blank, blank, &dummy, &dummy, 0, 0);

	XDefineCursor(ctx->display, win_int->window, cursor);
	XFreePixmap(ctx->display, blank);
	XFreeCursor(ctx->display, cursor);
}

void ftgr_mouse_show(t_ftgr_ctx *ctx, t_ftgr_win *win)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	XUndefineCursor(ctx->display, win_int->window);
}

t_iv2 ftgr_mouse_get_pos(t_ftgr_ctx *ctx, t_ftgr_win *win)
{
	Window root_return;
	Window child_return;
	int root_x_return;
	int root_y_return;
	unsigned mask_return;

	t_iv2 out;

	if (win)
	{
		t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

		XQueryPointer(ctx->display, win_int->window,
					  &root_return, &child_return, &root_x_return, &root_y_return,
					  &out.x, &out.y, &mask_return);
	}
	else
	{
		XQueryPointer(ctx->display, ctx->root,
					  &root_return, &child_return, &root_x_return, &root_y_return,
					  &out.x, &out.y, &mask_return);
	}
	return out;
}

bool ftgr_mouse_pressed(t_ftgr_ctx *ctx, S32 button)
{
	if (button < 0 || button >= 3)
		return FALSE;

	return !!(ctx->mouse[button]);
}

bool ftgr_mouse_down(t_ftgr_ctx *ctx, S32 button)
{
	if (button < 0 || button >= 3)
		return FALSE;
	
	return ctx->mouse[button] == _FTGR_MOUSE_DOWN;	
}

bool ftgr_mouse_released(t_ftgr_ctx *ctx, S32 button)
{
	(void)ctx;
	(void)button;
	return FALSE; //TODO: 
}

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:17:55 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/01 10:17:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int_win.h"

void		ftgr_mouse_move(t_ftgr_ctx *ctx, t_ftgr_win *win, t_iv2 pos)
{
	(void)ctx;
	(void)win;
	if (SetCursorPos(pos.x, pos.y) == FALSE)
		_ftgr_error();
}

void		ftgr_mouse_hide(t_ftgr_ctx *ctx, t_ftgr_win *win)
{
	(void)ctx;
	win->cursor_mode |= FTGR_CURSOR_HIDDEN;
}

void		ftgr_mouse_show(t_ftgr_ctx *ctx, t_ftgr_win *win)
{
	(void)ctx;
	win->cursor_mode &= ~FTGR_CURSOR_HIDDEN;
}

t_iv2		ftgr_mouse_get_pos(t_ftgr_ctx *ctx, t_ftgr_win *win)
{
	POINT p;
	if (GetCursorPos(&p) == FALSE)
		_ftgr_error();

	if (ScreenToClient(win->window_handle, &p) == FALSE)
		_ftgr_error();

	return ivec2(p.x, p.y);
}

bool	ftgr_mouse_pressed(t_ftgr_ctx *ctx, S32 button)
{
	switch (button)
	{
	case MOUSE_LEFT:
		return ctx->left_mouse_pressed;
	case MOUSE_MIDDLE:
		return ctx->middle_mouse_pressed;
	case MOUSE_RIGHT:
		return ctx->right_mouse_pressed;
	default:
		return FALSE;
	}
}

bool	ftgr_mouse_click(t_ftgr_ctx *ctx, S32 button)
{
	switch (button)
	{
	case MOUSE_LEFT:
		return ctx->left_mouse_clicked;
	case MOUSE_MIDDLE:
		return ctx->middle_mouse_clicked;
	case MOUSE_RIGHT:
		return ctx->right_mouse_clicked;
	default:
		return FALSE;
	}
}

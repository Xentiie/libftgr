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

#include "libftgr_int.h"

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

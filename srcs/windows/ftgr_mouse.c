/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftwin32_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:17:55 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/01 10:17:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftwin32_int.h"

void		ftwin32_mouse_move(t_ftwin32_ctx *ctx, t_ftwin32_win *win, t_iv2 pos)
{
	(void)ctx;
	(void)win;
	if (SetCursorPos(pos.x, pos.y) == FALSE)
		_ftwin32_error(ctx);
}

void		ftwin32_mouse_hide(t_ftwin32_ctx *ctx, t_ftwin32_win *win)
{
	(void)ctx;
	win->cursor_mode |= FTGR_CURSOR_HIDDEN;
}

void		ftwin32_mouse_show(t_ftwin32_ctx *ctx, t_ftwin32_win *win)
{
	(void)ctx;
	win->cursor_mode &= ~FTGR_CURSOR_HIDDEN;
}

t_iv2		ftwin32_mouse_get_pos(t_ftwin32_ctx *ctx, t_ftwin32_win *win)
{
	POINT p;
	if (GetCursorPos(&p) == FALSE)
		_ftwin32_error(ctx);

	if (ScreenToClient(win->window_handle, &p) == FALSE)
		_ftwin32_error(ctx);

	return ivec2(p.x, p.y);
}

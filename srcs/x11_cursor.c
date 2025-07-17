/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:42:27 by reclaire          #+#    #+#             */
/*   Updated: 2025/07/08 02:31:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftGFX_x11.h"
#if FT_OS_LINUX

#include "libft/bits/static_array_len.h"

#include <X11/Xcursor/Xcursor.h>

const_string ftgfxx11_cursor_name(enum e_ftGFX_cursor cursor)
{
	const string cursor_mapping[] = {
		[FTGFX_CURSOR_BLANK] = "",
		[FTGFX_CURSOR_DEFAULT] = "left_ptr",
		[FTGFX_CURSOR_TOP_SIDE] = "n-resize",
		[FTGFX_CURSOR_BOTTOM_SIDE] = "s-resize",
		[FTGFX_CURSOR_LEFT_SIDE] = "w-resize",
		[FTGFX_CURSOR_RIGHT_SIDE] = "e-resize",
		[FTGFX_CURSOR_TOP_LEFT_CORNER] = "nw-resize",
		[FTGFX_CURSOR_TOP_RIGHT_CORNER] = "ne-resize",
		[FTGFX_CURSOR_BOTTOM_LEFT_CORNER] = "sw-resize",
		[FTGFX_CURSOR_BOTTOM_RIGHT_CORNER] = "se-resize",
		[FTGFX_CURSOR_TEXT] = "text",
	};

	if (cursor < 0 || cursor >= statarray_len(cursor_mapping))
		return NULL;

	return cursor_mapping[cursor];
}

void ftGFX_cursor_hide(struct s_ftGFX_window *win)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	private = (struct s_ftGFX_ctx_private *)win->ctx->private;
	win_private = (struct s_ftGFX_window_private *)win->private;

	win_private->cursor_hidden = TRUE;
	XDefineCursor(private->display, win_private->window, private->cursors[FTGFX_CURSOR_BLANK]);
}

void ftGFX_cursor_show(struct s_ftGFX_window *win)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	private = (struct s_ftGFX_ctx_private *)win->ctx->private;
	win_private = (struct s_ftGFX_window_private *)win->private;

	win_private->cursor_hidden = TRUE;
	XDefineCursor(private->display, win_private->window, private->cursors[win_private->cursor_current]);
}

void ftGFX_cursor_set(struct s_ftGFX_window *win, enum e_ftGFX_cursor cursor)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	private = (struct s_ftGFX_ctx_private *)win->ctx->private;
	win_private = (struct s_ftGFX_window_private *)win->private;

	win_private->cursor_current = cursor;
	if (!win_private->cursor_hidden)
		XDefineCursor(private->display, win_private->window, private->cursors[win_private->cursor_current]);
}

#endif
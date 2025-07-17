/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:07:44 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/30 03:25:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftGFX_x11.h"
#if FT_OS_LINUX

#include "libft/bits/static_array_len.h"

#include <X11/Xcursor/Xcursor.h>

t_iv2 ftGFX_mouse_get_pos(struct s_ftGFX_ctx *ctx, struct s_ftGFX_window *win)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	t_iv2 out;
	Window dummy_root;
	Window dummy_child;
	S32 dummy_root_x;
	S32 dummy_root_y;
	U32 dummy_mask;

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	if (win)
	{
		win_private = (struct s_ftGFX_window_private *)win->private;

		XQueryPointer(private->display, win_private->window,
					  &dummy_root, &dummy_child, &dummy_root_x, &dummy_root_y,
					  &out.x, &out.y, &dummy_mask);
	}
	else
	{
		XQueryPointer(private->display, private->root,
					  &dummy_root, &dummy_child, &dummy_root_x, &dummy_root_y,
					  &out.x, &out.y, &dummy_mask);
	}
	return out;
}

void ftGFX_mouse_set_pos(struct s_ftGFX_ctx *ctx, struct s_ftGFX_window *win, t_iv2 pos)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	if (win)
	{
		win_private = (struct s_ftGFX_window_private *)win->private;
		XWarpPointer(private->display, None, win_private->window, 0, 0, 0, 0, pos.x, pos.y);
	}
	else
		XWarpPointer(private->display, None, None, 0, 0, 0, 0, pos.x, pos.y);
}

#endif
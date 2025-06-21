/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:07:44 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/09 00:34:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftGFX_x11.h"
#if FT_OS_LINUX

bool ftgfxx11_init_blank_cursor(struct s_ftGFX_window *win)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	static char blank_pixmap_data[1] = {0};
	XColor dummy;

	private = (struct s_ftGFX_ctx_private *)win->ctx->private;
	win_private = (struct s_ftGFX_window_private *)win->private;

	dummy = (XColor){0};
	if ((win_private->blank_cursor.pixmap = XCreateBitmapFromData(private->display,
																  win_private->window,
																  blank_pixmap_data,
																  1, 1)) == None)
		FT_RET_ERR(FALSE, FT_EINVOP);

	if ((win_private->blank_cursor.cursor = XCreatePixmapCursor(private->display,
																win_private->blank_cursor.pixmap,
																win_private->blank_cursor.pixmap,
																&dummy, &dummy, 0, 0)) == None)
	{
		XFreePixmap(private->display, win_private->blank_cursor.pixmap);
		FT_RET_ERR(FALSE, FT_EINVOP);
	}

	win_private->blank_cursor.has_blank_cursor = TRUE;

	FT_RET_OK(TRUE);
}

void ftgfxx11_destroy_blank_cursor(struct s_ftGFX_window *win)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	private = (struct s_ftGFX_ctx_private *)win->ctx->private;
	win_private = (struct s_ftGFX_window_private *)win->private;

	if (win_private->blank_cursor.has_blank_cursor)
	{
		XFreePixmap(private->display, win_private->blank_cursor.pixmap);
		XFreeCursor(private->display, win_private->blank_cursor.cursor);
	}
}

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

void ftGFX_mouse_hide(struct s_ftGFX_window *win)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	private = (struct s_ftGFX_ctx_private *)win->ctx->private;
	win_private = (struct s_ftGFX_window_private *)win->private;

	if (!win_private->blank_cursor.has_blank_cursor)
	{
		if (!ftgfxx11_init_blank_cursor(win))
			return;
	}

	XDefineCursor(private->display, win_private->window, win_private->blank_cursor.cursor);
}

void ftGFX_mouse_show(struct s_ftGFX_window *win)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window_private *win_private;

	private = (struct s_ftGFX_ctx_private *)win->ctx->private;
	win_private = (struct s_ftGFX_window_private *)win->private;

	XUndefineCursor(private->display, win_private->window);
}

#endif
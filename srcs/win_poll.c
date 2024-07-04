/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:06:13 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 18:06:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_win_int.h"

#ifdef FT_OS_WIN
#include <stdio.h>

static void update_time(t_ftgr_ctx *ctx)
{
	t_time tmp;
	clk_get(&tmp);
	ctx->delta_time = clk_diff_float(&ctx->delta_time_clk, &tmp);
	ctx->delta_time_clk = tmp;
}

bool ftgr_poll(t_ftgr_ctx *ctx)
{
	update_time(ctx);
	_ftwin32_keys_cleanup(ctx);

	ctx->left_mouse_clicked = FALSE;
	ctx->middle_mouse_clicked = FALSE;
	ctx->right_mouse_clicked = FALSE;

	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
	{
		switch (msg.message)
		{
		case WM_QUIT:
			return FALSE;
		default:
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	return TRUE;
}

bool ftgr_wait(t_ftgr_ctx *ctx)
{
	while (!XPending(ctx->display))
		;
	return ftgr_poll(ctx);
}

#endif
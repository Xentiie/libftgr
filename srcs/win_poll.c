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
	ft_clk_get(&tmp);
	ctx->delta_time = ft_clk_diff_float(&ctx->delta_time_clk, &tmp);
	ctx->delta_time_clk = tmp;
}

static bool _ftgr_process_event(t_ftgr_ctx *ctx, MSG msg)
{
	if (msg.message == WM_QUIT)
	{
		printf("quit\n");
		return FALSE;
	}

	TranslateMessage(&msg);
	DispatchMessage(&msg);
	return TRUE;
}

bool ftgr_poll(t_ftgr_ctx *ctx)
{
	update_time(ctx);
	_ftwin32_keys_cleanup(ctx);

	ctx->left_mouse_clicked = FALSE;
	ctx->middle_mouse_clicked = FALSE;
	ctx->right_mouse_clicked = FALSE;

	MSG msg;
	bool ret;
	while ((ret = PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) != 0)
	{
		if (ret == -1)
		{
			_ftgr_error();
			return TRUE;
		}
		else if (!_ftgr_process_event(ctx, msg))
			return FALSE;
	}
	return TRUE;
}

bool ftgr_wait(t_ftgr_ctx *ctx)
{
	update_time(ctx);
	_ftwin32_keys_cleanup(ctx);

	ctx->left_mouse_clicked = FALSE;
	ctx->middle_mouse_clicked = FALSE;
	ctx->right_mouse_clicked = FALSE;

	MSG msg;
	bool ret = GetMessage(&msg, NULL, 0, 0);
	if (ret == -1)
	{
		_ftgr_error();
		return TRUE;
	}
	else
		return _ftgr_process_event(ctx, msg);
}

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftwin32_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:06:13 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 18:06:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftwin32_int.h"

#include <stdio.h>

void call_loop_hook(void *func)
{
	((void (*)())(func))();
}

void ftwin32_loop(t_ftwin32_ctx *ctx)
{
	ctx->run = TRUE;

	while (ctx->run)
	{
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		//while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Task manager can send WM_QUIT
			if (msg.message == WM_QUIT)
			{
				// Close all windows
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}

		ft_lstiter(ctx->loop_hooks, call_loop_hook);
	}
}

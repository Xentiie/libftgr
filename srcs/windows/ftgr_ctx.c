/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_ctx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:06:29 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 18:06:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"

t_ftgr_ctx   *ftgr_create_ctx()
{
    t_ftgr_ctx   *ctx = malloc(sizeof(t_ftgr_ctx));
	if (!ctx)
		return NULL;


    ctx->instance_handle = GetModuleHandleW(NULL);
	if (!ctx->instance_handle)
	{
		_ftgr_error();
		free(ctx);
		return NULL;
	}

	ctx->main_window_class = 0;

	ctx->windows = NULL;

	clk_get(&ctx->global_time);
	clk_get(&ctx->delta_time_clk);

	ctx->keys = NULL;

	return ctx;
}

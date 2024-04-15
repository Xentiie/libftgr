/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftwin32_ctx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:06:29 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 18:06:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftwin32_int.h"

t_ftwin32_ctx   *ftwin32_create_ctx()
{
    t_ftwin32_ctx   *ctx = malloc(sizeof(t_ftwin32_ctx));
	if (!ctx)
		return NULL;


    ctx->instance_handle = GetModuleHandleW(NULL);
	if (!ctx->instance_handle)
	{
		free(ctx);
		return NULL;
	}

	ctx->main_window_class = 0;

	ctx->windows = NULL;
	ctx->loop_hooks = NULL;

	ctx->run = FALSE;

	ctx->on_quit = NULL;
	ctx->error_callback = NULL;

	return ctx;
}

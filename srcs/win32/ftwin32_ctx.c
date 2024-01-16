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

    ctx->instance_handle = GetModuleHandle(NULL);
	if (!ctx->instance_handle)
	{
		return NULL;
	}

	ctx->main_window_class = 0;

	ctx->windows = NULL;
	ctx->loop_hooks = NULL;

	ctx->run = FALSE;
	
	return ctx;
}

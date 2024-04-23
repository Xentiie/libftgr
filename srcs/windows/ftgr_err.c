/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftwin32_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:15:32 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/02 23:15:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftwin32_int.h"

void ftwin32_set_error_callback(t_ftwin32_ctx *ctx, void (*callback)())
{
	ctx->error_callback = callback;
}

void _ftwin32_error(t_ftwin32_ctx *ctx)
{
	if (ctx->error_callback)
		ctx->error_callback();
}


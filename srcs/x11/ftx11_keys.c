/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx11_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:26:57 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/10 11:13:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftx11_int.h"

void ftx11_key_autorepeat(t_ftx11_ctx *ctx, bool active)
{
	if (active)
		XAutoRepeatOn(ctx->display);
	else
		XAutoRepeatOff(ctx->display);
}

bool ftx11_is_key_down(t_ftx11_ctx *ctx)
{
	(void)ctx;
	return FALSE;
}

bool ftx11_is_key_up(t_ftx11_ctx *ctx)
{
	(void)ctx;
	return FALSE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:26:57 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/27 04:07:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftGFX_x11.h"
#ifdef FT_OS_LINUX

#include "libft/limits.h"

void ftgfxx11_keys_reset(struct s_ftGFX_ctx *ctx)
{
	for (U16 i = 0; i < sizeof(ctx->keys) / sizeof(ctx->keys[0]); i++)
	{
		if (ctx->keys[i] == FTGFX_KEY_PRESSED)
			ctx->keys[i] = FTGFX_KEY_DOWN;
		else if (ctx->keys[i] == FTGFX_KEY_RELEASED)
			ctx->keys[i] = FTGFX_KEY_UP;
	}

	for (U8 i = 0; i < sizeof(ctx->mouse) / sizeof(ctx->mouse[0]); i++)
	{
		if (ctx->mouse[i] == FTGFX_MOUSE_PRESSED)
			ctx->mouse[i] = FTGFX_MOUSE_DOWN;
		else if (ctx->mouse[i] == FTGFX_MOUSE_RELEASED)
			ctx->mouse[i] = FTGFX_MOUSE_UP;
	}
}

void ftGFX_key_autorepeat(struct s_ftGFX_ctx *ctx, bool active)
{
	struct s_ftGFX_ctx_private *private;

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	if (active)
		XAutoRepeatOn(private->display);
	else
		XAutoRepeatOff(private->display);
	XFlush(private->display);
}

#endif
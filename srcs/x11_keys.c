/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:26:57 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/01 13:13:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_x11_int.h"
#ifdef FT_OS_LINUX

#include "libft/limits.h"

/*
==================================================
*/

void _ftx11_register_key_down(t_ftgr_ctx *ctx, U32 key)
{
	if (key >= 255)
		return;
	ctx->keys[key] = _FTGR_KEY_DOWN;
}

void _ftx11_register_key_up(t_ftgr_ctx *ctx, U32 key)
{
	if (key >= 255)
		return;
	ctx->keys[key] = FALSE;
}

void _ftx11_keys_cleanup(t_ftgr_ctx *ctx)
{
	for (U16 i = 0; i < sizeof(ctx->keys) / sizeof(ctx->keys[0]); i++)
	{
		if (ctx->keys[i] == _FTGR_KEY_DOWN)
			ctx->keys[i] = _FTGR_KEY_PRESSED;
	}

	for (U8 i = 0; i < sizeof(ctx->mouse) / sizeof(ctx->mouse[0]); i++)
	{
		if (ctx->mouse[i] == _FTGR_MOUSE_DOWN)
			ctx->mouse[i] = _FTGR_MOUSE_PRESSED;
	}
}
/*
==================================================
*/

bool ftgr_is_key_pressed(t_ftgr_ctx *ctx, U8 key)
{
	return !!(ctx->keys[key]);
}

bool ftgr_is_key_down(t_ftgr_ctx *ctx, U8 key)
{
	return ctx->keys[key] == _FTGR_KEY_DOWN;
}

bool ftgr_is_key_up(t_ftgr_ctx *ctx, U8 key)
{
	(void)ctx;
	(void)key;
	return FALSE; //TODO: 
}

void ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active)
{
	if (active)
		XAutoRepeatOn(ctx->display);
	else
		XAutoRepeatOff(ctx->display);
	XFlush(ctx->display);
}

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:29:50 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/16 22:34:49 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_win_int.h"

#ifdef FT_OS_WIN

void _ftwin32_register_key_down(t_ftgr_ctx *ctx, U8 key)
{
	ctx->keys[key].down = TRUE;
	ctx->keys[key].pressed = TRUE;
}

void _ftwin32_register_key_up(t_ftgr_ctx *ctx, U8 key)
{
	ctx->keys[key].up = TRUE;
	ctx->keys[key].pressed = FALSE;
}

void _ftwin32_keys_cleanup(t_ftgr_ctx *ctx)
{
	for (U32 i = 0; i < sizeof(ctx->keys)/sizeof(ctx->keys[0]); i++)
	{
		ctx->keys[i].down = FALSE;
		ctx->keys[i].up = FALSE;
	}

	ctx->left_mouse_released = FALSE;
	ctx->middle_mouse_released = FALSE;
	ctx->right_mouse_released = FALSE;
}

bool ftgr_is_key_pressed(t_ftgr_ctx *ctx, U8 key)
{
	return ctx->keys[key].pressed;
}

bool ftgr_is_key_down(t_ftgr_ctx *ctx, U8 key)
{
	return ctx->keys[key].down;
}

bool ftgr_is_key_up(t_ftgr_ctx *ctx, U8 key)
{
	return ctx->keys[key].up;
}

void ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active)
{
    ctx->key_autorepeat = active;
}

#endif
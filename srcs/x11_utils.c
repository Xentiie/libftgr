/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:38:56 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/26 22:08:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftGFX_x11.h"

#ifdef FT_OS_LINUX

U8 ftgfxx11_x11_to_ftgfx_mouse_button(U32 x11_mouse_button)
{
	const U8 x11_to_ftgfx[] = {
		[0] = (U8)-1, /* Invalid */
		[1] = FTGFX_MOUSE_LEFT,
		[2] = FTGFX_MOUSE_MIDDLE,
		[3] = FTGFX_MOUSE_RIGHT,
		[4] = FTGFX_MOUSE_SCROLLWHEEL_UP,
		[5] = FTGFX_MOUSE_SCROLLWHEEL_DOWN,
		[6] = FTGFX_MOUSE_SCROLLWHEEL_PUSH_LEFT,
		[7] = FTGFX_MOUSE_SCROLLWHEEL_PUSH_RIGHT,
		[8] = FTGFX_MOUSE_SIDE_1,
		[9] = FTGFX_MOUSE_SIDE_2,	
	};

	if (x11_mouse_button > statarray_len(x11_to_ftgfx))
		FT_RET_ERR((U8)-1, FT_ERANGE);
	return x11_to_ftgfx[x11_mouse_button];
}

t_iv2 ftGFX_get_screen_size(struct s_ftGFX_ctx *ctx)
{
	struct s_ftGFX_ctx_private *private;
	XWindowAttributes	attr;

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	XGetWindowAttributes(private->display, private->root, &attr);
	return ivec2(attr.width, attr.height);
}

#endif
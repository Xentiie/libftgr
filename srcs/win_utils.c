/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:38:56 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/04 16:46:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_win_int.h"

#ifdef FT_OS_WIN

t_iv2 ftgr_get_screen_size(t_ftgr_ctx *ctx)
{
	XWindowAttributes	attr;
	XGetWindowAttributes(ctx->display, ctx->root, &attr);

	return ivec2(attr.width, attr.height);
}

#endif
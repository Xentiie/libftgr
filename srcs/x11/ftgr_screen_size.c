/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_screen_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:10:06 by reclaire          #+#    #+#             */
/*   Updated: 2024/04/16 22:36:30 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"

t_iv2 ftgr_get_screen_size(t_ftgr_ctx *ctx)
{
	XWindowAttributes	attr;
	XGetWindowAttributes(ctx->display, ctx->root, &attr);

	return ivec2(attr.width, attr.height);
}

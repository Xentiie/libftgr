/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx11_screen_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:10:06 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/10 08:11:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftx11_int.h"

t_iv2 ftx11_get_screen_size(t_ftx11_ctx *ctx)
{
	XWindowAttributes	attr;
	XGetWindowAttributes(ctx->display, ctx->root, &attr);

	return ivec2(attr.width, attr.height);
}

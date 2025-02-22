/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:32:16 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/14 03:07:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/time.h"
#include "libft/io.h"
#include "libft/maths.h"
#include "libft/debug.h"

#include <time.h>
#include <stdlib.h>

void ftgr_stretch_img_bound(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect)
{
	dst_rect.x = ft_clamp(0, dst->size.x, dst_rect.x);
	dst_rect.y = ft_clamp(0, dst->size.y, dst_rect.y);
	dst_rect.z = ft_clamp(0, dst->size.x, dst_rect.z);
	dst_rect.w = ft_clamp(0, dst->size.y, dst_rect.w);

	src_rect.x = ft_clamp(0, dst->size.x, src_rect.x);
	src_rect.y = ft_clamp(0, dst->size.y, src_rect.y);
	src_rect.z = ft_clamp(0, dst->size.x, src_rect.z);
	src_rect.w = ft_clamp(0, dst->size.y, src_rect.w);

	S32 dst_w = dst_rect.z - dst_rect.x;
	S32 dst_h = dst_rect.w - dst_rect.y;

	S32 src_w = src_rect.z - src_rect.x;
	S32 src_h = src_rect.w - src_rect.y;

	S32 *x_vals = alloca(sizeof(S32) * dst_w);
	for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		x_vals[x - dst_rect.x] = (S32)(src_rect.x + ((x - dst_rect.x) / (F32)dst_w) * src_w);

	for (S32 y = dst_rect.y; y < dst_rect.w; y++)
	{
		for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		{
			t_color *dst_addr = ftgr_get_pixel(dst, x, y);
			t_color *src_addr = ftgr_get_pixel(src, x_vals[x - dst_rect.x], ((S32)(src_rect.y + ((y - dst_rect.y) / (F32)dst_h) * src_h)));
			*dst_addr = *src_addr;
		}
	}
}

void ftgr_stretch_img2(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect, t_color col)
{
	dst_rect.x = ft_clamp(0, dst->size.x, dst_rect.x);
	dst_rect.y = ft_clamp(0, dst->size.y, dst_rect.y);
	dst_rect.z = ft_clamp(0, dst->size.x, dst_rect.z);
	dst_rect.w = ft_clamp(0, dst->size.y, dst_rect.w);

	src_rect.x = ft_clamp(0, dst->size.x, src_rect.x);
	src_rect.y = ft_clamp(0, dst->size.y, src_rect.y);
	src_rect.z = ft_clamp(0, dst->size.x, src_rect.z);
	src_rect.w = ft_clamp(0, dst->size.y, src_rect.w);

	S32 dst_w = dst_rect.z - dst_rect.x;
	S32 dst_h = dst_rect.w - dst_rect.y;

	S32 src_w = src_rect.z - src_rect.x;
	S32 src_h = src_rect.w - src_rect.y;

	S32 *x_vals = alloca(sizeof(S32) * dst_w);
	for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		x_vals[x - dst_rect.x] = (S32)(src_rect.x + ((x - dst_rect.x) / (F32)dst_w) * src_w); // TODO: ici on a (x / y * z) ou y et z sont constant. Peut etre simplifié

	for (S32 y = dst_rect.y; y < dst_rect.w; y++)
	{
		for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		{
			t_color *dst_addr = ftgr_get_pixel(dst, x, y);
			t_color *src_addr = ftgr_get_pixel(src, x_vals[x - dst_rect.x], ((S32)(src_rect.y + ((y - dst_rect.y) / (F32)dst_h) * src_h)));
			t_color src_col = *src_addr;
			t_color dst_col = *dst_addr;

			src_col.r *= (col.r / 255.0f);
			src_col.g *= (col.g / 255.0f);
			src_col.b *= (col.b / 255.0f);

			*dst_addr = ftgr_alpha_blend(dst_col, src_col);
		}
	}
}

void ftgr_cpy_img(t_image *dst, t_iv2 dst_pos, t_image *src, t_iv4 src_rect)
{
	src_rect = ft_imin4(ivec4(dst_pos.x, dst_pos.y, dst->size.x, dst->size.y), src_rect);
	for (S32 y = src_rect.y; y < src_rect.w; y++)
		for (S32 x = src_rect.x; x < src_rect.z; x++)
			*ftgr_get_pixel(dst, x + dst_pos.x, y + dst_pos.y) = *ftgr_get_pixel(src, x, y);
}

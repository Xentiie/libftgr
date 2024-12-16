/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:22:58 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/10 19:15:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

void ftgr_draw_line_horizontal_bound(t_ftgr_img *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound)
{
	t_color *ptr;
	S32 xlen;

	bound.x = ft_imax(bound.x, 0);
	bound.y = ft_imax(bound.y, 0);
	bound.z = ft_imin(bound.z, img->size.x);
	bound.w = ft_imin(bound.w, img->size.y);

	if (p1.y < bound.y || p1.y >= bound.w)
		return;

	p1.x = ft_clamp(bound.x, bound.z - 1, p1.x);
	x2 = ft_clamp(bound.x, bound.z - 1, x2);

	xlen = ft_abs(p1.x - x2);

	ptr = ftgr_get_pixel(img, ft_imin(p1.x, x2), p1.y);
	for (S32 i = 0; i < xlen; i++, ptr++)
		*ptr = col;
}

void ftgr_draw_line_horizontal(t_ftgr_img *img, t_iv2 p1, S32 x2, t_color col)
{
	ftgr_draw_line_horizontal_bound(img, p1, x2, col, ivec4(0, 0, img->size.x, img->size.y));
}

void ftgr_draw_line_horizontal_bound2(t_ftgr_img *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound)
{
	t_color *ptr;
	S32 xlen;

	bound.x = ft_imax(bound.x, 0);
	bound.y = ft_imax(bound.y, 0);
	bound.z = ft_imin(bound.z, img->size.x);
	bound.w = ft_imin(bound.w, img->size.y);

	if (p1.y < bound.y || p1.y >= bound.w)
		return;

	p1.x = ft_clamp(bound.x, bound.z, p1.x);
	x2 = ft_clamp(bound.x, bound.z, x2);

	xlen = ft_abs(p1.x - x2);

	ptr = ftgr_get_pixel(img, ft_imin(p1.x, x2), p1.y);
	for (S32 i = 0; i < xlen; i++, ptr++)
		*ptr = ftgr_alpha_blend(*ptr, col);
}

void ftgr_draw_line_horizontal2(t_ftgr_img *img, t_iv2 p1, S32 x2, t_color col)
{
	ftgr_draw_line_horizontal_bound2(img, p1, x2, col, ivec4(0, 0, img->size.x, img->size.y));
}

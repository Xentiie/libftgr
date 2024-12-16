/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:22:58 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/10 19:17:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

void ftgr_draw_line_vertical_bound(t_ftgr_img *img, t_iv2 p1, S32 y2, t_color col, t_iv4 bound)
{
	t_color *ptr;
	S32 ylen;

	bound.x = ft_imax(bound.x, 0);
	bound.y = ft_imax(bound.y, 0);
	bound.z = ft_imin(bound.z, img->size.x);
	bound.w = ft_imin(bound.w, img->size.y);

	if (p1.x < bound.x || p1.x >= bound.w)
		return;

	p1.y = ft_clamp(bound.y, bound.w, p1.y);
	y2 = ft_clamp(bound.y, bound.w, y2);

	ylen = ft_abs(p1.y - y2);

	ptr = ftgr_get_pixel(img, p1.x, ft_imin(p1.y, y2));
	for (S32 y = 0; y < ylen; y++, ptr += img->size.x)
		*ptr = col;
}

void ftgr_draw_line_vertical(t_ftgr_img *img, t_iv2 p1, S32 y2, t_color col)
{
	ftgr_draw_line_vertical_bound(img, p1, y2, col, ivec4(0, 0, img->size.x, img->size.y));
}

void ftgr_draw_line_vertical_bound2(t_ftgr_img *img, t_iv2 p1, S32 y2, t_color col, t_iv4 bound)
{
	t_color *ptr;
	S32 ylen;

	bound.x = ft_imax(bound.x, 0);
	bound.y = ft_imax(bound.y, 0);
	bound.z = ft_imin(bound.z, img->size.x);
	bound.w = ft_imin(bound.w, img->size.y);

	if (p1.x < bound.x || p1.x >= bound.w)
		return;

	p1.y = ft_clamp(bound.y, bound.w, p1.y);
	y2 = ft_clamp(bound.y, bound.w, y2);

	ylen = ft_abs(p1.y - y2);

	ptr = ftgr_get_pixel(img, p1.x, ft_imin(p1.y, y2));
	for (S32 y = 0; y < ylen; y++, ptr += img->size.x)
		*ptr = ftgr_alpha_blend(*ptr, col);
}

void ftgr_draw_line_vertical2(t_ftgr_img *img, t_iv2 p1, S32 y2, t_color col)
{
	ftgr_draw_line_vertical_bound2(img, p1, y2, col, ivec4(0, 0, img->size.x, img->size.y));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:48:33 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/14 03:07:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

inline static void draw_bounded_pixel(t_image *img, S32 x, S32 y, t_color col, t_iv4 bound)
{
	if (x >= bound.x && x < bound.z && y >= bound.y && y < bound.w)
		*ftgr_get_pixel(img, x, y) = col;
}

inline static void draw_bounded_pixel2(t_image *img, S32 x, S32 y, t_color col, t_iv4 bound)
{
	t_color *addr;

	if (x >= bound.x && x < bound.z && y >= bound.y && y < bound.w)
	{
		addr = ftgr_get_pixel(img, x, y);
		*addr = ftgr_alpha_blend(*addr, col);
	}
}

void ftgr_draw_circle_bound(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound)
{
	S32 x;
	S32 y;
	S32 d;

	bound.x = ft_imax(bound.x, 0);
	bound.y = ft_imax(bound.y, 0);
	bound.z = ft_imin(bound.z, img->size.x);
	bound.w = ft_imin(bound.w, img->size.y);

	x = 0;
	y = radius;
	d = 1 - radius;

	draw_bounded_pixel(img, pos.x + x, pos.y + y, col, bound);
	draw_bounded_pixel(img, pos.x + x, pos.y - y, col, bound);
	draw_bounded_pixel(img, pos.x + y, pos.y + x, col, bound);
	draw_bounded_pixel(img, pos.x + y, pos.y - x, col, bound);
	draw_bounded_pixel(img, pos.x - x, pos.y + y, col, bound);
	draw_bounded_pixel(img, pos.x - x, pos.y - y, col, bound);
	draw_bounded_pixel(img, pos.x - y, pos.y + x, col, bound);
	draw_bounded_pixel(img, pos.x - y, pos.y - x, col, bound);

	while (x < y)
	{
		x++;

		if (d < 0)
			d += 2 * x + 1;
		else
		{
			y--;
			d += 2 * (x - y) + 1;
		}

		draw_bounded_pixel(img, pos.x + x, pos.y + y, col, bound);
		draw_bounded_pixel(img, pos.x + x, pos.y - y, col, bound);
		draw_bounded_pixel(img, pos.x + y, pos.y + x, col, bound);
		draw_bounded_pixel(img, pos.x + y, pos.y - x, col, bound);
		draw_bounded_pixel(img, pos.x - x, pos.y + y, col, bound);
		draw_bounded_pixel(img, pos.x - x, pos.y - y, col, bound);
		draw_bounded_pixel(img, pos.x - y, pos.y + x, col, bound);
		draw_bounded_pixel(img, pos.x - y, pos.y - x, col, bound);
	}
}

void ftgr_draw_circle(t_image *img, t_iv2 pos, S32 radius, t_color col)
{
	ftgr_draw_circle_bound(img, pos, radius, col, ivec4(0, 0, img->size.x, img->size.y));
}

void ftgr_draw_circle_bound2(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound)
{
	S32 x;
	S32 y;
	S32 d;

	bound.x = ft_imax(bound.x, 0);
	bound.y = ft_imax(bound.y, 0);
	bound.z = ft_imin(bound.z, img->size.x);
	bound.w = ft_imin(bound.w, img->size.y);

	x = 0;
	y = radius;
	d = 1 - radius;

	draw_bounded_pixel2(img, pos.x + x, pos.y + y, col, bound);
	draw_bounded_pixel2(img, pos.x + x, pos.y - y, col, bound);
	draw_bounded_pixel2(img, pos.x + y, pos.y + x, col, bound);
	draw_bounded_pixel2(img, pos.x + y, pos.y - x, col, bound);
	draw_bounded_pixel2(img, pos.x - x, pos.y + y, col, bound);
	draw_bounded_pixel2(img, pos.x - x, pos.y - y, col, bound);
	draw_bounded_pixel2(img, pos.x - y, pos.y + x, col, bound);
	draw_bounded_pixel2(img, pos.x - y, pos.y - x, col, bound);

	while (x < y)
	{
		x++;

		if (d < 0)
			d += 2 * x + 1;
		else
		{
			y--;
			d += 2 * (x - y) + 1;
		}

		draw_bounded_pixel2(img, pos.x + x, pos.y + y, col, bound);
		draw_bounded_pixel2(img, pos.x + x, pos.y - y, col, bound);
		draw_bounded_pixel2(img, pos.x + y, pos.y + x, col, bound);
		draw_bounded_pixel2(img, pos.x + y, pos.y - x, col, bound);
		draw_bounded_pixel2(img, pos.x - x, pos.y + y, col, bound);
		draw_bounded_pixel2(img, pos.x - x, pos.y - y, col, bound);
		draw_bounded_pixel2(img, pos.x - y, pos.y + x, col, bound);
		draw_bounded_pixel2(img, pos.x - y, pos.y - x, col, bound);
	}
}

void ftgr_draw_circle2(t_image *img, t_iv2 pos, S32 radius, t_color col)
{
	ftgr_draw_circle_bound2(img, pos, radius, col, ivec4(0, 0, img->size.x, img->size.y));
}

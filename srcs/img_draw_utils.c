/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:32:16 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/14 02:19:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

void ftgr_draw_line(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_color col)
{
	int dx = abs(p2.x - p1.x), sx = p1.x < p2.x ? 1 : -1;
	int dy = abs(p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	for (;;)
	{
		ftgr_set_pixel(img, ivec2(p1.x, p1.y), col);
		if (p1.x == p2.x && p1.y == p2.y)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			p1.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			p1.y += sy;
		}
	}
}

void ftgr_draw_line_e(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p))
{
	t_iv2 _p1 = p1, _p2 = p2;

	int dx = abs(p2.x - p1.x), sx = p1.x < p2.x ? 1 : -1;
	int dy = abs(p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	for (;;)
	{
		ftgr_set_pixel(img, ivec2(p1.x, p1.y), eval(_p1, _p2, p1));
		if (p1.x == p2.x && p1.y == p2.y)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			p1.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			p1.y += sy;
		}
	}
}

void ftgr_draw_rect(t_ftgr_img *img, t_iv2 c1, t_iv2 c2, t_color col)
{
	ftgr_draw_line(img, ivec2(c1.x, c1.y), ivec2(c2.x, c1.y), col);
	ftgr_draw_line(img, ivec2(c2.x, c1.y), ivec2(c2.x, c2.y), col);
	ftgr_draw_line(img, ivec2(c2.x, c2.y), ivec2(c1.x, c2.y), col);
	ftgr_draw_line(img, ivec2(c1.x, c2.y), ivec2(c1.x, c1.y), col);
}

void ftgr_draw_rect_e(t_ftgr_img *img, t_iv2 c1, t_iv2 c2, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p))
{
	ftgr_draw_line_e(img, ivec2(c1.x, c1.y), ivec2(c2.x, c1.y), eval);
	ftgr_draw_line_e(img, ivec2(c2.x, c1.y), ivec2(c2.x, c2.y), eval);
	ftgr_draw_line_e(img, ivec2(c2.x, c2.y), ivec2(c1.x, c2.y), eval);
	ftgr_draw_line_e(img, ivec2(c1.x, c2.y), ivec2(c1.x, c1.y), eval);
}

void ftgr_fill_rect(t_ftgr_img *img, t_iv2 c1, t_iv2 c2, t_color col)
{
	for (S32 y = c1.y; y < c2.y; y++)
		for (S32 x = c1.x; x < c2.x; x++)
			ftgr_set_pixel(img, ivec2(x, y), col);
}

void ftgr_fill_rect_e(t_ftgr_img *img, t_iv2 c1, t_iv2 c2, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p))
{
	for (S32 y = c1.y; y < c2.y; y++)
		for (S32 x = c1.x; x < c2.x; x++)
		{
			t_iv2 p = ivec2(x, y);
			ftgr_set_pixel(img, p, eval(c1, c2, p));
		}
}

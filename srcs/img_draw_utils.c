/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:32:16 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/09 23:40:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include <stdlib.h>

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

void ftgr_draw_line_horizontal(t_ftgr_img *img, t_iv2 p1, S32 x2, t_color col)
{
	for (S32 x = p1.x; x <= x2; x++)
		ftgr_set_pixel(img, ivec2(x, p1.y), col);
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

void ftgr_draw_bezier(t_ftgr_img *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res)
{
	t_v2 prev = p1;
	for (S32 i = 0; i < res; i++)
	{
		F32 t = (i + 1.0f) / res;
		t_v2 p_on_curve = ft_bezier_interp(p1, p2, p3, t);
		ftgr_draw_line(img, vec2_int(prev), vec2_int(p_on_curve), col);
		prev = p_on_curve;
	}
}

void ftgr_draw_circle(t_ftgr_img *img, t_iv2 pos, S32 radius, t_color col)
{
	S32 x = 0, y = radius;
	S32 d = 1 - radius; // Decision parameter

	// Draw initial points on all octants
	ftgr_set_pixel(img, ivec2(pos.x + x, pos.y + y), col);
	ftgr_set_pixel(img, ivec2(pos.x - x, pos.y + y), col);
	ftgr_set_pixel(img, ivec2(pos.x + x, pos.y - y), col);
	ftgr_set_pixel(img, ivec2(pos.x - x, pos.y - y), col);
	ftgr_set_pixel(img, ivec2(pos.x + y, pos.y + x), col);
	ftgr_set_pixel(img, ivec2(pos.x - y, pos.y + x), col);
	ftgr_set_pixel(img, ivec2(pos.x + y, pos.y - x), col);
	ftgr_set_pixel(img, ivec2(pos.x - y, pos.y - x), col);

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

		// Draw points for each octant
		ftgr_set_pixel(img, ivec2(pos.x + x, pos.y + y), col);
		ftgr_set_pixel(img, ivec2(pos.x - x, pos.y + y), col);
		ftgr_set_pixel(img, ivec2(pos.x + x, pos.y - y), col);
		ftgr_set_pixel(img, ivec2(pos.x - x, pos.y - y), col);
		ftgr_set_pixel(img, ivec2(pos.x + y, pos.y + x), col);
		ftgr_set_pixel(img, ivec2(pos.x - y, pos.y + x), col);
		ftgr_set_pixel(img, ivec2(pos.x + y, pos.y - x), col);
		ftgr_set_pixel(img, ivec2(pos.x - y, pos.y - x), col);
	}
}

void ftgr_draw_disc(t_ftgr_img *img, t_iv2 pos, S32 radius, t_color col)
{
	S32 x = 0, y = radius;
	S32 d = 1 - radius; // Decision parameter

	// Draw and fill the initial points on all octants
	ftgr_draw_line_horizontal(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col);
	ftgr_draw_line_horizontal(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col);
	ftgr_draw_line_horizontal(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col);
	ftgr_draw_line_horizontal(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col);

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

		// Draw and fill horizontal lines for each segment
		ftgr_draw_line_horizontal(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col);
		ftgr_draw_line_horizontal(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col);
		ftgr_draw_line_horizontal(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col);
		ftgr_draw_line_horizontal(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:16:13 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/06 20:19:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

void ftgr_draw_disc_bound(t_ftgr_img *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound)
{
	S32 x = 0, y = radius;
	S32 d = 1 - radius; // Decision parameter

	// Draw and fill the initial points on all octants
	ftgr_draw_line_horizontal_bound(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col, bound);
	ftgr_draw_line_horizontal_bound(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col, bound);
	ftgr_draw_line_horizontal_bound(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col, bound);
	ftgr_draw_line_horizontal_bound(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col, bound);

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
		ftgr_draw_line_horizontal_bound(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col, bound);
		ftgr_draw_line_horizontal_bound(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col, bound);
		ftgr_draw_line_horizontal_bound(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col, bound);
		ftgr_draw_line_horizontal_bound(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col, bound);
	}
}

void ftgr_draw_disc(t_ftgr_img *img, t_iv2 pos, S32 radius, t_color col)
{
	ftgr_draw_disc_bound(img, pos, radius, col, ivec4(0, 0, img->size.x, img->size.y));
}

void ftgr_draw_disc_bound2(t_ftgr_img *img, t_iv2 pos, S32 radius, t_color col, t_iv4 rect)
{
	S32 x = 0, y = radius;
	S32 d = 1 - radius; // Decision parameter

	// Draw and fill the initial points on all octants
	ftgr_draw_line_horizontal_bound2(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col, rect);
	ftgr_draw_line_horizontal_bound2(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col, rect);
	ftgr_draw_line_horizontal_bound2(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col, rect);
	ftgr_draw_line_horizontal_bound2(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col, rect);

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
		ftgr_draw_line_horizontal_bound2(img, ivec2(pos.x - x, pos.y + y), pos.x + x, col, rect);
		ftgr_draw_line_horizontal_bound2(img, ivec2(pos.x - x, pos.y - y), pos.x + x, col, rect);
		ftgr_draw_line_horizontal_bound2(img, ivec2(pos.x - y, pos.y + x), pos.x + y, col, rect);
		ftgr_draw_line_horizontal_bound2(img, ivec2(pos.x - y, pos.y - x), pos.x + y, col, rect);
	}
}

void ftgr_draw_disc2(t_ftgr_img *img, t_iv2 pos, S32 radius, t_color col)
{
	ftgr_draw_disc_bound2(img, pos, radius, col, ivec4(0, 0, img->size.x, img->size.y));
}

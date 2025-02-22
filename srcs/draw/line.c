/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:22:58 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/14 03:07:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

#include "libft/maths.h"
#include "libft/io.h"

#define INSIDE 0
#define LEFT (1 << 0)
#define RIGHT (1 << 1)
#define BOTTOM (1 << 2)
#define TOP (1 << 3)
static U8 line_draw_intersect(t_iv2 p, t_iv4 bound)
{
	U8 outcode = INSIDE;

	if (p.x < bound.x)
		outcode |= LEFT;
	else if (p.x >= bound.z)
		outcode |= RIGHT;

	if (p.y < bound.y)
		outcode |= BOTTOM;
	else if (p.y >= bound.w)
		outcode |= TOP;

	return outcode;
}

static bool line_accept(t_iv2 *p1, t_iv2 *p2, S32 width, S32 height, t_iv4 bound)
{
	U8 intersect1;
	U8 intersect2;

	intersect1 = line_draw_intersect(*p1, bound);
	intersect2 = line_draw_intersect(*p2, bound);

	while (TRUE)
	{
		if (!(intersect1 | intersect2)) /* both inside */
			return TRUE;
		else if (intersect1 & intersect2) /* both outside */
			return FALSE;
		else
		{
			t_iv2 intersection;
			U8 intersect_out = (intersect1 != INSIDE) ? intersect1 : intersect2;
			if (intersect_out & TOP)
			{
				intersection.x = p1->x + (p2->x - p1->x) * (height - 1 - p1->y) / (p2->y - p1->y);
				intersection.y = height - 1;
			}
			else if (intersect_out & BOTTOM)
			{
				intersection.x = p1->x + (p2->x - p1->x) * (0 - p1->y) / (p2->y - p1->y);
				intersection.y = 0;
			}
			else if (intersect_out & RIGHT)
			{
				intersection.y = p1->y + (p2->y - p1->y) * (width - 1 - p1->x) / (p2->x - p1->x);
				intersection.x = width - 1;
			}
			else if (intersect_out & LEFT)
			{
				intersection.y = p1->y + (p2->y - p1->y) * (0 - p1->x) / (p2->x - p1->x);
				intersection.x = 0;
			}
			else
				intersection = ivec2(0, 0);

			if (intersect_out == intersect1)
			{
				*p1 = intersection;
				intersect1 = line_draw_intersect(*p1, bound);
			}
			else
			{
				*p2 = intersection;
				intersect2 = line_draw_intersect(*p2, bound);
			}
		}
	}
}

FUNCTION_HOT void ftgr_draw_line_bound(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, t_iv4 bound)
{
	S32 width;
	S32 height;

	bound.x = ft_imax(bound.x, 0);
	bound.y = ft_imax(bound.y, 0);
	bound.z = ft_imin(bound.z, img->size.x);
	bound.w = ft_imin(bound.w, img->size.y);

	width = bound.z - bound.x;
	height = bound.w - bound.y;

	if (line_accept(&p1, &p2, width, height, bound))
	{
		S32 dx = ft_abs(p2.x - p1.x), dy = ft_abs(p2.y - p1.y);
		S32 sx = (p1.x < p2.x) ? 1 : -1;
		S32 sy = (p1.y < p2.y) ? 1 : -1;
		S32 err = dx - dy, e2;

		while (TRUE)
		{
			//if (p1.x >= 0 && p1.x < img->size.x && p1.y >= 0 && p1.y < img->size.y)
				*ftgr_get_pixel(img, p1.x, p1.y) = col;

			if (p1.x == p2.x && p1.y == p2.y)
				break;

			e2 = 2 * err;
			if (e2 > -dy)
			{
				err -= dy;
				p1.x += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				p1.y += sy;
			}
		}
		ft_printf("Accept (%d %d) (%d %d)\n", p1.x, p1.y, p2.x, p2.y);
	}
	else
		ft_printf("Deny (%d %d) (%d %d)\n", p1.x, p1.y, p2.x, p2.y);
}

void ftgr_draw_line(t_image *img, t_iv2 p1, t_iv2 p2, t_color col)
{
	ftgr_draw_line_bound(img, p1, p2, col, ivec4(0, 0, img->size.x, img->size.y));
}

FUNCTION_HOT void ftgr_draw_line_bound2(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, t_iv4 bound)
{
	t_color *addr;
	S32 width;
	S32 height;

	bound.x = ft_imax(bound.x, 0);
	bound.y = ft_imax(bound.y, 0);
	bound.z = ft_imin(bound.z, img->size.x);
	bound.w = ft_imin(bound.w, img->size.y);

	width = bound.z - bound.x;
	height = bound.w - bound.y;

	if (line_accept(&p1, &p2, width, height, bound))
	{
		S32 dx = ft_abs(p2.x - p1.x), dy = ft_abs(p2.y - p1.y);
		S32 sx = (p1.x < p2.x) ? 1 : -1;
		S32 sy = (p1.y < p2.y) ? 1 : -1;
		S32 err = dx - dy, e2;

		while (TRUE)
		{
			// if (p1.x >= 0 && p1.x < img->size.x && p1.y >= 0 && p1.y < img->size.y)
			//{
			addr = ftgr_get_pixel(img, p1.x, p1.y);
			*addr = ftgr_alpha_blend(*addr, col);
			//}

			if (p1.x == p2.x && p1.y == p2.y)
				break;

			e2 = 2 * err;
			if (e2 > -dy)
			{
				err -= dy;
				p1.x += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				p1.y += sy;
			}
		}
	}
}

void ftgr_draw_line2(t_image *img, t_iv2 p1, t_iv2 p2, t_color col)
{
	ftgr_draw_line_bound2(img, p1, p2, col, ivec4(0, 0, img->size.x, img->size.y));
}

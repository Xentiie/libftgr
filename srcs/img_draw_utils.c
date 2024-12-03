/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:32:16 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/03 16:31:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/time.h"
#include "libft/maths.h"
#include "libft/debug.h"

#include <time.h>
#include <stdlib.h>

void ftgr_set_pixel(t_ftgr_img *img, t_iv2 p, t_color col)
{
	U32 c = ftgr_color_to_int(col);
	*(U32 *)ftgr_get_pixel_addr(img, p.x, p.y) = c;
}

t_color ftgr_get_pixel(t_ftgr_img *img, t_iv2 p)
{
	return ftgr_int_to_color(*(U32 *)ftgr_get_pixel_addr(img, p.x, p.y));
}

t_color ftgr_rand_color(U32 seed)
{
	return (t_color){.r = ft_frand(seed) * 255, .g = ft_frand(seed + 1) * 255, .b = ft_frand(seed + 2) * 255, .a = 255};
}

t_color ftgr_alpha_blend(t_color under, t_color over)
{
	F32 over_a;
	F32 under_a;

	over_a = (F32)over.a / (F32)255;
	under_a = (F32)under.a / (F32)255;
	return (t_color){
		.r = over_a * over.r + (1 - over_a) * under.r * under_a,
		.g = over_a * over.g + (1 - over_a) * under.g * under_a,
		.b = over_a * over.b + (1 - over_a) * under.b * under_a,
		.a = (over_a + under_a * (1 - over_a)) * 255};
}

#define INSIDE 0
#define LEFT (1 << 0)
#define RIGHT (1 << 1)
#define BOTTOM (1 << 2)
#define TOP (1 << 3)
static U8 line_draw_intersect(t_iv2 p, S32 width, S32 height)
{
	U8 outcode = INSIDE;

	if (p.x < 0)
		outcode |= LEFT;
	else if (p.x >= width)
		outcode |= RIGHT;

	if (p.y < 0)
		outcode |= BOTTOM;
	else if (p.y >= height)
		outcode |= TOP;

	return outcode;
}

FUNCTION_HOT void ftgr_draw_line(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_color col)
{
	U32 col_i = ftgr_color_to_int(col);
	S32 width = img->size.x;
	S32 height = img->size.y;

	U8 intersect1 = line_draw_intersect(p1, width, height);
	U8 intersect2 = line_draw_intersect(p2, width, height);
	// printf("(%d %d):{%u %u %u %u} (%d %d)\n", p1.x, p1.y, !!(intersect1 & INSIDE), !!(intersect1 & LEFT), !!(intersect1 & RIGHT), !!(intersect1 & BOTTOM), !!(intersect1 & TOP),
	//	   p2.x, p2.y, !!(intersect2 & INSIDE), !!(intersect2 & LEFT), !!(intersect2 & RIGHT), !!(intersect2 & BOTTOM), !!(intersect2 & TOP));

	bool accept = FALSE;
	// bool accept = TRUE;

	while (TRUE)
	// while (FALSE)
	{
		if (!(intersect1 | intersect2)) /* both inside */
		{
			accept = TRUE;
			break;
		}
		else if (intersect1 & intersect2) /* both outside */
			return;
		else
		{
			t_iv2 intersection;
			U8 intersect_out = (intersect1 != INSIDE) ? intersect1 : intersect2;
			if (intersect_out & TOP)
			{
				intersection.x = p1.x + (p2.x - p1.x) * (height - 1 - p1.y) / (p2.y - p1.y);
				intersection.y = height - 1;
			}
			else if (intersect_out & BOTTOM)
			{
				intersection.x = p1.x + (p2.x - p1.x) * (0 - p1.y) / (p2.y - p1.y);
				intersection.y = 0;
			}
			else if (intersect_out & RIGHT)
			{
				intersection.y = p1.y + (p2.y - p1.y) * (width - 1 - p1.x) / (p2.x - p1.x);
				intersection.x = width - 1;
			}
			else if (intersect_out & LEFT)
			{
				intersection.y = p1.y + (p2.y - p1.y) * (0 - p1.x) / (p2.x - p1.x);
				intersection.x = 0;
			}
			else
			{
				intersection = ivec2(0, 0);
				ft_debug_break();
			}

			if (intersect_out == intersect1)
			{
				p1 = intersection;
				intersect1 = line_draw_intersect(p1, width, height);
			}
			else
			{
				p2 = intersection;
				intersect2 = line_draw_intersect(p2, width, height);
			}
		}
	}

	if (accept)
	{
		S32 dx = abs(p2.x - p1.x), dy = abs(p2.y - p1.y);
		S32 sx = (p1.x < p2.x) ? 1 : -1;
		S32 sy = (p1.y < p2.y) ? 1 : -1;
		S32 err = dx - dy, e2;

		while (TRUE)
		{
			if (p1.x >= 0 && p1.x < img->size.x && p1.y >= 0 && p1.y < img->size.y)
				ft_memcpy(ftgr_get_pixel_addr(img, p1.x, p1.y), &col_i, img->bpp);

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

FUNCTION_HOT void ftgr_draw_line_e(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_iv4 lp1lp2, void *data), void *data)
{
	t_iv4 lp1lp2 = ivec4(p1.x, p1.y, p2.x, p2.y);
	int width = img->size.x;
	int height = img->size.y;

	int intersect1 = line_draw_intersect(p1, width, height);
	int intersect2 = line_draw_intersect(p2, width, height);

	bool accept = FALSE;
	while (TRUE)
	{
		if (!(intersect1 | intersect2)) /* both inside */
		{
			accept = TRUE;
			break;
		}
		else if (intersect1 & intersect2) /* both outside */
			return;
		else
		{
			t_iv2 intersection;
			U8 intersect_out = (intersect1 != INSIDE) ? intersect1 : intersect2;
			if (intersect_out & TOP)
			{
				intersection.x = p1.x + (p2.x - p1.x) * (height - 1 - p1.y) / (p2.y - p1.y);
				intersection.y = height - 1;
			}
			else if (intersect_out & BOTTOM)
			{
				intersection.x = p1.x + (p2.x - p1.x) * (0 - p1.y) / (p2.y - p1.y);
				intersection.y = 0;
			}
			else if (intersect_out & RIGHT)
			{
				intersection.y = p1.y + (p2.y - p1.y) * (width - 1 - p1.x) / (p2.x - p1.x);
				intersection.x = width - 1;
			}
			else if (intersect_out & LEFT)
			{
				intersection.y = p1.y + (p2.y - p1.y) * (0 - p1.x) / (p2.x - p1.x);
				intersection.x = 0;
			}
			else
			{
				intersection = ivec2(0, 0);
				ft_debug_break();
			}

			if (intersect_out == intersect1)
			{
				p1 = intersection;
				intersect1 = line_draw_intersect(p1, width, height);
			}
			else
			{
				p2 = intersection;
				intersect2 = line_draw_intersect(p2, width, height);
			}
		}
	}

	if (accept)
	{
		S32 dx = abs(p2.x - p1.x), dy = abs(p2.y - p1.y);
		S32 sx = (p1.x < p2.x) ? 1 : -1;
		S32 sy = (p1.y < p2.y) ? 1 : -1;
		S32 err = dx - dy, e2;

		while (TRUE)
		{
			if (p1.x >= 0 && p1.x < img->size.x && p1.y >= 0 && p1.y < img->size.y)
				eval(img, ivec2(p1.x, p1.y), lp1lp2, data);

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

void ftgr_draw_line_horizontal(t_ftgr_img *img, t_iv2 p1, S32 x2, t_color col)
{
	U32 col_i = ftgr_color_to_int(col);
	U32 *addr;

	if (p1.y < 0 || p1.y >= img->size.y)
		return;

	//TODO: bpp
	p1.x = ft_clamp(0, img->size.x - 1, p1.x);
	x2 = ft_clamp(0, img->size.x - 1, x2);

	addr = (U32 *)ftgr_get_pixel_addr(img, ft_imin(p1.x, x2), p1.y);
	for (S32 i = 0; i < ft_abs(p1.x - x2); i++)
		addr[i] = col_i;
}

void ftgr_draw_line_horizontal_e(t_ftgr_img *img, t_iv2 p1, S32 x2, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_iv4 lp1lp2, void *data), void *data)
{
	t_iv4 lp1lp2 = ivec4(p1.x, p1.y, x2, p1.y);

	if (p1.y < 0 || p1.y >= img->size.y)
		return;

	p1.x = ft_clamp(0, img->size.x - 1, p1.x);
	x2 = ft_clamp(0, img->size.x - 1, x2);
	for (S32 x = ft_imin(p1.x, x2); x < ft_abs(p1.x - x2); x++)
		eval(img, ivec2(x, p1.y), lp1lp2, data);
}

void ftgr_draw_line_vertical(t_ftgr_img *img, t_iv2 p1, S32 y2, t_color col)
{
	U32 col_i = ftgr_color_to_int(col);

	if (p1.x < 0 || p1.x >= img->size.x)
		return;

	p1.y = ft_clamp(0, img->size.y - 1, p1.y);
	y2 = ft_clamp(0, img->size.y - 1, y2);
	for (U64 y = p1.y; y < (U64)y2; y++)
		ft_memcpy(ftgr_get_pixel_addr(img, p1.x, y), &col_i, img->bpp);
}

void ftgr_draw_line_vertical_e(t_ftgr_img *img, t_iv2 p1, S32 y2, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_iv4 lp1lp2, void *data), void *data)
{
	t_iv4 lp1lp2 = ivec4(p1.x, p1.y, y2, p1.y);

	if (p1.x < 0 || p1.x >= img->size.x)
		return;

	p1.y = ft_clamp(0, img->size.y - 1, p1.y);
	y2 = ft_clamp(0, img->size.y - 1, y2);
	for (S32 y = ft_imin(p1.y, y2); y < ft_abs(p1.y - y2); y++)
		eval(img, ivec2(p1.x, y), lp1lp2, data);
}

void ftgr_draw_rect(t_ftgr_img *img, t_iv4 rect, t_color col)
{
	ftgr_draw_line_horizontal(img, ivec2(rect.x, rect.y), rect.z, col);
	ftgr_draw_line_horizontal(img, ivec2(rect.x, rect.w), rect.z, col);
	ftgr_draw_line_vertical(img, ivec2(rect.x, rect.y), rect.w, col);
	ftgr_draw_line_vertical(img, ivec2(rect.z, rect.y), rect.w, col);
}

void ftgr_draw_rect_e(t_ftgr_img *img, t_iv4 rect, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_iv4 rect, void *data), void *data)
{
	t_iv4 rect_full = rect;

	rect.x = ft_clamp(0, img->size.x, rect.x);
	rect.y = ft_clamp(0, img->size.y, rect.y);
	rect.z = ft_clamp(0, img->size.x, rect.z);
	rect.w = ft_clamp(0, img->size.y, rect.w);

	for (S32 y = rect.y; y < rect.y; y++)
	{
		eval(img, ivec2(rect.x, y), rect_full, data);
		eval(img, ivec2(rect.z, y), rect_full, data);
	}
	for (S32 x = rect.x; x < rect.x; x++)
	{
		eval(img, ivec2(x, rect.y), rect_full, data);
		eval(img, ivec2(x, rect.w), rect_full, data);
	}
}

void ftgr_fill_rect(t_ftgr_img *img, t_iv4 rect, t_color col)
{
	U32 col_i = ftgr_color_to_int(col);

	rect.x = ft_clamp(0, img->size.x, rect.x);
	rect.y = ft_clamp(0, img->size.y, rect.y);
	rect.z = ft_clamp(0, img->size.x, rect.z);
	rect.w = ft_clamp(0, img->size.y, rect.w);

	for (S32 y = rect.y; y < rect.w; y++)
		for (S32 x = rect.x; x < rect.z; x++)
			ft_memcpy(ftgr_get_pixel_addr(img, x, y), &col_i, img->bpp);
}

void ftgr_fill_rect_e(t_ftgr_img *img, t_iv4 rect, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_iv4 rect, void *data), void *data)
{
	t_iv4 rect_full = rect;

	rect.x = ft_clamp(0, img->size.x, rect.x);
	rect.y = ft_clamp(0, img->size.y, rect.y);
	rect.z = ft_clamp(0, img->size.x, rect.z);
	rect.w = ft_clamp(0, img->size.y, rect.w);

	for (S32 y = rect.y; y < rect.y; y++)
	{
		for (S32 x = rect.x; x < rect.x; x++)
		{
			// col_i = ftgr_color_to_int(eval(ivec2(rect.x, rect.y), ivec2(rect.z, rect.w), ivec2(x, y)));
			// ft_memcpy(ftgr_get_pixel_addr(img, x, y), &col_i, img->bpp);
			eval(img, ivec2(x, y), rect_full, data);
		}
	}
}

void ftgr_draw_triangle(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col)
{
	ftgr_draw_line(img, p1, p2, col);
	ftgr_draw_line(img, p2, p3, col);
	ftgr_draw_line(img, p3, p1, col);
}

static F32 edgeFunction(t_v2 a, t_v2 b, t_v2 c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}
FUNCTION_HOT static void _ftgr_draw_triangle_e(t_ftgr_img *img, t_iv2 xy, t_iv4 lp1lp2, void *tris_data)
{
	void (*eval)(t_ftgr_img *img, t_iv2 xy, t_v3 w, void *data) = *((void (**)(t_ftgr_img *img, t_iv2 xy, t_v3 w, void *data))tris_data);
	void *data = *(void **)(((U8 *)tris_data) + sizeof(void *));
	t_v2 p1 = vec2(lp1lp2.x, lp1lp2.y);
	t_v2 p2 = vec2(lp1lp2.z, lp1lp2.w);
	t_v2 p3 = ivec2_flt(*((t_iv2 *)(((U8 *)tris_data) + sizeof(void *) * 2)));

	F32 area = edgeFunction(p1, p2, p3);
	if (area < 0)
		area = edgeFunction(p3, p2, p1);
	t_v2 _p2 = vec2(xy.x + 0.5, xy.y + 0.5);
	t_v3 w = vec3(edgeFunction(p3, p1, _p2),
				  edgeFunction(p2, p3, _p2),
				  edgeFunction(p1, p2, _p2));

	w.x /= area;
	w.y /= area;
	w.z /= area;
	/*
		t_v2 t1 = {0, 0};
		t_v2 t2 = {1, 0};
		t_v2 t3 = {1, 1};
		t_v2 uv;
		uv.x = w.x * t1.x + w.y * t2.x + w.z * t3.x;
		uv.y = w.x * t1.y + w.y * t2.y + w.z * t3.y;
		uv.y = 1 - uv.y;
	*/
	eval(img, xy, w, data);
}
void ftgr_draw_triangle_e(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_v3 w, void *data), void *data)
{
	struct
	{
		void *eval;
		void *data;
		t_iv2 p3;
	} tris_data = {
		.eval = eval,
		.data = data,
		.p3 = p3};
	ftgr_draw_line_e(img, p1, p2, _ftgr_draw_triangle_e, &tris_data);
	ftgr_draw_line_e(img, p2, p3, _ftgr_draw_triangle_e, &tris_data);
	ftgr_draw_line_e(img, p3, p1, _ftgr_draw_triangle_e, &tris_data);
}

FUNCTION_HOT void ftgr_fill_triangle_e(t_ftgr_img *img, t_iv2 ip1, t_iv2 ip2, t_iv2 ip3, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_v3 w, void *data), void *data)
{
	t_v2 p1, p2, p3;
	F32 area;
	t_iv2 bbox_min, bbox_max;
	S32 x, y;

	p1 = ivec2_flt(ip1);
	p2 = ivec2_flt(ip2);
	p3 = ivec2_flt(ip3);
	area = edgeFunction(p3, p2, p1);

	bbox_min = vec2_int(ft_ceil2(ft_fmin2_3(p1, p2, p3)));
	bbox_max = vec2_int(ft_ceil2(ft_fmax2_3(p1, p2, p3)));

	bbox_min = ft_imax2(bbox_min, ivec2(0, 0));
	bbox_max = ft_imin2(bbox_max, img->size);

	x = bbox_min.x;
	while (x < bbox_max.x)
	{
		y = bbox_min.y;
		while (y < bbox_max.y)
		{

			t_v2 _p2 = vec2(x + 0.5, y + 0.5);
			t_v3 w = vec3(edgeFunction(p3, p1, _p2),
						  edgeFunction(p2, p3, _p2),
						  edgeFunction(p1, p2, _p2));
			if (w.x >= 0 && w.y >= 0 && w.z >= 0)
			{
				w.x /= area;
				w.y /= area;
				w.z /= area;
				eval(img, ivec2(x, y), w, data);
			}
			y++;
		}
		x++;
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
	U32 col_i = ftgr_color_to_int(col);

	if (pos.x - radius < 0 || pos.x + radius >= img->size.x || pos.y - radius < 0 || pos.y + radius >= img->size.y)
		return;

	// Draw initial points on all octants
	ft_memcpy(ftgr_get_pixel_addr(img, pos.x + x, pos.y + y), &col_i, img->bpp);
	ft_memcpy(ftgr_get_pixel_addr(img, pos.x - x, pos.y + y), &col_i, img->bpp);
	ft_memcpy(ftgr_get_pixel_addr(img, pos.x + x, pos.y - y), &col_i, img->bpp);
	ft_memcpy(ftgr_get_pixel_addr(img, pos.x - x, pos.y - y), &col_i, img->bpp);
	ft_memcpy(ftgr_get_pixel_addr(img, pos.x + y, pos.y + x), &col_i, img->bpp);
	ft_memcpy(ftgr_get_pixel_addr(img, pos.x - y, pos.y + x), &col_i, img->bpp);
	ft_memcpy(ftgr_get_pixel_addr(img, pos.x + y, pos.y - x), &col_i, img->bpp);
	ft_memcpy(ftgr_get_pixel_addr(img, pos.x - y, pos.y - x), &col_i, img->bpp);

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
		ft_memcpy(ftgr_get_pixel_addr(img, pos.x + x, pos.y + y), &col_i, img->bpp);
		ft_memcpy(ftgr_get_pixel_addr(img, pos.x - x, pos.y + y), &col_i, img->bpp);
		ft_memcpy(ftgr_get_pixel_addr(img, pos.x + x, pos.y - y), &col_i, img->bpp);
		ft_memcpy(ftgr_get_pixel_addr(img, pos.x - x, pos.y - y), &col_i, img->bpp);
		ft_memcpy(ftgr_get_pixel_addr(img, pos.x + y, pos.y + x), &col_i, img->bpp);
		ft_memcpy(ftgr_get_pixel_addr(img, pos.x - y, pos.y + x), &col_i, img->bpp);
		ft_memcpy(ftgr_get_pixel_addr(img, pos.x + y, pos.y - x), &col_i, img->bpp);
		ft_memcpy(ftgr_get_pixel_addr(img, pos.x - y, pos.y - x), &col_i, img->bpp);
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

void ftgr_stretch_img(t_ftgr_img *dst, t_iv4 dst_rect, t_ftgr_img *src, t_iv4 src_rect)
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
			U32 dst_addr = ((x + y * dst->size.x) * dst->bpp);
			U32 src_addr = ((
								x_vals[x - dst_rect.x] +
								((S32)(src_rect.y + ((y - dst_rect.y) / (F32)dst_h) * src_h) * src->size.x)) *
							src->bpp);
			*(U32 *)(dst->data + dst_addr) = *(U32 *)(src->data + src_addr);
		}
	}
}

void ftgr_stretch_img2(t_ftgr_img *dst, t_iv4 dst_rect, t_ftgr_img *src, t_iv4 src_rect, t_color col)
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
			U32 dst_addr = ((x + y * dst->size.x) * dst->bpp);
			U32 src_addr = ((
								x_vals[x - dst_rect.x] +
								((S32)(src_rect.y + ((y - dst_rect.y) / (F32)dst_h) * src_h) * src->size.x)) *
							src->bpp);
			t_color src_col = ftgr_int_to_color(*(U32 *)(src->data + src_addr));
			t_color dst_col = ftgr_int_to_color(*(U32 *)(dst->data + dst_addr));

			src_col.r *= (col.r / 255.0f);
			src_col.g *= (col.g / 255.0f);
			src_col.b *= (col.b / 255.0f);

			*(U32 *)(dst->data + dst_addr) = ftgr_color_to_int(ftgr_alpha_blend(dst_col, src_col));
		}
	}
}

void ftgr_cpy_img(t_ftgr_img *dst, t_iv2 dst_pos, t_ftgr_img *src, t_iv4 src_rect)
{
	src_rect = ft_imin4(ivec4(dst_pos.x, dst_pos.y, dst->size.x, dst->size.y), src_rect);
	for (S32 y = src_rect.y; y < src_rect.w; y++)
		for (S32 x = src_rect.x; x < src_rect.z; x++)
		{
			U32 dst_addr = ((x + dst_pos.x + ((y + dst_pos.y) * dst->size.x)) * dst->bpp);
			U32 src_addr = ((x + y * dst->size.x) * dst->bpp);
			*(U32 *)(dst->data + dst_addr) = *(U32 *)(src->data + src_addr);
		}
}

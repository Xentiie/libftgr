/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:32:16 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/09 00:51:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/time.h"
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

t_color ftgr_rand_color()
{
	t_time t;
	clk_get(&t);
	return (t_color){.r = ft_frand(t.nanoseconds) * 255, .g = ft_frand(t.nanoseconds + 1) * 255, .b = ft_frand(t.nanoseconds + 2) * 255, .a = 255};
}

void ftgr_draw_line(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_color col)
{
	U32 col_i = ftgr_color_to_int(col);
	int dx = abs(p2.x - p1.x), sx = p1.x < p2.x ? 1 : -1;
	int dy = abs(p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	for (;;)
	{
		*(U32 *)ftgr_get_pixel_addr(img, p1.x, p1.y) = col_i;
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
	U32 col_i = ftgr_color_to_int(col);
	for (S32 x = p1.x; x <= x2; x++)
		*(U32 *)ftgr_get_pixel_addr(img, x, p1.y) = col_i;
}

void ftgr_draw_line_e(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p))
{
	t_iv2 st = p1, nd = p2;
	U32 col_i;

	int dx = abs(p2.x - p1.x), sx = p1.x < p2.x ? 1 : -1;
	int dy = abs(p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	for (;;)
	{
		col_i = ftgr_color_to_int(eval(st, nd, p1));
		*(U32 *)ftgr_get_pixel_addr(img, p1.x, p1.y) = col_i;
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

void ftgr_draw_rect(t_ftgr_img *img, t_iv4 rect, t_color col)
{
	ftgr_draw_line(img, ivec2(rect.x, rect.y), ivec2(rect.z, rect.y), col);
	ftgr_draw_line(img, ivec2(rect.z, rect.y), ivec2(rect.z, rect.w), col);
	ftgr_draw_line(img, ivec2(rect.z, rect.w), ivec2(rect.x, rect.w), col);
	ftgr_draw_line(img, ivec2(rect.x, rect.w), ivec2(rect.x, rect.y), col);
}

void ftgr_draw_rect_e(t_ftgr_img *img, t_iv4 rect, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p))
{
	ftgr_draw_line_e(img, ivec2(rect.x, rect.y), ivec2(rect.z, rect.y), eval);
	ftgr_draw_line_e(img, ivec2(rect.z, rect.y), ivec2(rect.z, rect.w), eval);
	ftgr_draw_line_e(img, ivec2(rect.z, rect.w), ivec2(rect.x, rect.w), eval);
	ftgr_draw_line_e(img, ivec2(rect.x, rect.w), ivec2(rect.x, rect.y), eval);
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
			*(U32 *)ftgr_get_pixel_addr(img, x, y) = col_i;
}

void ftgr_fill_rect_e(t_ftgr_img *img, t_iv4 rect, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p))
{
	for (S32 y = rect.y; y < rect.y; y++)
		for (S32 x = rect.x; x < rect.x; x++)
			*(U32 *)ftgr_get_pixel_addr(img, x, y) = ftgr_color_to_int(eval(ivec2(rect.x, rect.y), ivec2(rect.z, rect.w), ivec2(x, y)));
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

	// Draw initial points on all octants
	*(U32 *)ftgr_get_pixel_addr(img, pos.x + x, pos.y + y) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x - x, pos.y + y) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x + x, pos.y - y) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x - x, pos.y - y) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x + y, pos.y + x) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x - y, pos.y + x) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x + y, pos.y - x) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x - y, pos.y - x) = col_i;

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
	*(U32 *)ftgr_get_pixel_addr(img, pos.x + x, pos.y + y) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x - x, pos.y + y) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x + x, pos.y - y) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x - x, pos.y - y) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x + y, pos.y + x) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x - y, pos.y + x) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x + y, pos.y - x) = col_i;
	*(U32 *)ftgr_get_pixel_addr(img, pos.x - y, pos.y - x) = col_i;
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


void ftgr_stretch_img2(t_ftgr_img *dst, t_iv4 dst_rect, t_iv4 dst_rect_st_nd, t_ftgr_img *src, t_iv4 src_rect)
{
	S32 dst_w = dst_rect.z - dst_rect.x;
	S32 dst_h = dst_rect.w - dst_rect.y;

	S32 src_w = src_rect.z - src_rect.x;
	S32 src_h = src_rect.w - src_rect.y;

	S32 *x_vals = alloca(sizeof(S32) * dst_w);
	for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		x_vals[x - dst_rect.x] = (S32)(src_rect.x + ((x - dst_rect.x) / (F32)dst_w) * src_w);

	for (S32 y = dst_rect_st_nd.y; y < dst_rect_st_nd.w; y++)
	{
		for (S32 x = dst_rect_st_nd.x; x < dst_rect_st_nd.z; x++)
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

void ftgr_stretch_img(t_ftgr_img *dst, t_iv4 dst_rect, t_ftgr_img *src, t_iv4 src_rect)
{
	if (dst_rect.x < 0) dst_rect.x = 0;
	if (dst_rect.y < 0) dst_rect.y = 0;
	if (dst_rect.z < 0) dst_rect.z = 0;
	if (dst_rect.w < 0) dst_rect.w = 0;
	if (src_rect.x < 0) src_rect.x = 0;
	if (src_rect.y < 0) src_rect.y = 0;
	if (src_rect.z < 0) src_rect.z = 0;
	if (src_rect.w < 0) src_rect.w = 0;

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

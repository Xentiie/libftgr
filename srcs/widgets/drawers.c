/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:48:01 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/12 13:26:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

#if defined(WIDGETS_H)
static void __ftgr_wdrawer_stretch_img_cpu(t_ftgr_img *out, t_widget *widget, t_iv4 rect, union u_widget_data data)
{
	t_iv4 widget_rect;

	widget_rect = ftgr_widget_rect(widget);
	ftgr_stretch_img2(out, widget_rect, data.img[0], ivec4(0, 0, data.img[0]->size.x, data.img[0]->size.y), COL_WHITE);
}

bool ftgr_wdrawer_stretch_img_cpu(t_widget *widget, t_ftgr_img *img)
{
	t_widget_drawer drawer;

	if (widget == NULL || img == NULL)
		return FALSE;
	drawer.draw_f = __ftgr_wdrawer_stretch_img_cpu;
	drawer.data.img[0] = img;
	ftgr_add_wdrawer(widget, drawer);
	return TRUE;
}

static void __ftgr_wdrawer_copy_img_cpu(t_ftgr_img *out, t_widget *widget, t_iv4 rect, union u_widget_data data)
{
	t_iv4 widget_rect;
	
	widget_rect = ftgr_widget_rect(widget);
	ftgr_cpy_img(
		out, ivec2(widget_rect.x, widget_rect.y),
		data.img[0], ivec4(0, 0, data.img[0]->size.x, data.img[0]->size.y));
}

bool ftgr_wdrawer_copy_img_cpu(t_widget *widget, t_ftgr_img *img)
{
	t_widget_drawer drawer;

	if (widget == NULL || img == NULL)
		return FALSE;
	drawer.draw_f = __ftgr_wdrawer_copy_img_cpu;
	drawer.data.img[0] = img;
	ftgr_add_wdrawer(widget, drawer);
	return TRUE;
}

static void __ftgr_wdrawer_fill_rect(t_ftgr_img *out, t_widget *widget, t_iv4 rect, union u_widget_data data)
{
	t_iv4 widget_rect;
	
	widget_rect = ftgr_widget_rect(widget);
	ftgr_fill_rect_bound2(out, widget_rect, data.color[0], rect);
}

bool ftgr_wdrawer_fill_rect(t_widget *widget, t_color color)
{
	t_widget_drawer drawer;

	if (widget == NULL)
		return FALSE;
	drawer.draw_f = __ftgr_wdrawer_fill_rect;
	drawer.data.color[0] = color;
	ftgr_add_wdrawer(widget, drawer);
	return TRUE;
}

static void __ftgr_wdrawer_draw_rect(t_ftgr_img *out, t_widget *widget, t_iv4 rect, union u_widget_data data)
{
	t_iv4 widget_rect;

	widget_rect = ftgr_widget_rect(widget);
	ftgr_draw_rect_bound2(out, widget_rect, data.color[0], rect);
}

bool ftgr_wdrawer_draw_rect(t_widget *widget, t_color color)
{
	t_widget_drawer drawer;

	if (widget == NULL)
		return FALSE;
	drawer.draw_f = __ftgr_wdrawer_draw_rect;
	drawer.data.color[0] = color;
	ftgr_add_wdrawer(widget, drawer);
	return TRUE;
}

static void __ftgr_wdrawer_draw_text(t_ftgr_img *out, t_widget *widget, t_iv4 rect, union u_widget_data data)
{
	t_iv4 widget_rect;

	widget_rect = ftgr_widget_rect(widget);
	ftgr_draw_bitmap_text(out, widget_rect, data.ptr[0], *(t_text *)(data.ptr[1]), data.color[4]);
}

bool ftgr_wdrawer_draw_text(t_widget *widget, t_bitmap *bitmap, t_text *text, t_color color)
{
	t_widget_drawer drawer;

	if (widget == NULL)
		return FALSE;
	drawer.draw_f = __ftgr_wdrawer_draw_text;
	drawer.data.ptr[0] = bitmap;
	drawer.data.ptr[1] = text;
	drawer.data.color[4] = color;
	ftgr_add_wdrawer(widget, drawer);
	return TRUE;
}

static void __ftgr_wdrawer_draw_disc(t_ftgr_img *out, t_widget *widget, t_iv4 rect, union u_widget_data data)
{
	U32 radius;
	t_color col;
	t_iv4 widget_rect;
	t_iv2 widget_size_h;

	col = data.color[0];
	radius = data.u32[1];
	widget_size_h = ivec2_div(widget->size, ivec2(2, 2));
	widget_rect = ftgr_widget_rect(widget);
	ftgr_draw_disc_bound2(out, ivec2(widget_rect.x + widget_size_h.x, widget_rect.y + widget_size_h.y), radius, col, rect);
}

bool ftgr_wdrawer_draw_disc(t_widget *widget, U32 radius, t_color color)
{
	t_widget_drawer drawer;

	if (widget == NULL)
		return FALSE;
	drawer.draw_f = __ftgr_wdrawer_draw_disc;
	drawer.data.color[0] = color;
	drawer.data.u32[1] = radius;
	ftgr_add_wdrawer(widget, drawer);
	return TRUE;
}
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:48:01 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/18 16:48:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"


static void __ftgr_wdrawer_stretch_img_cpu(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, union u_widget_data data)
{
	ftgr_stretch_img(
		out, ivec4(abs_pos.x, abs_pos.y, abs_pos.x + widget->size.x, abs_pos.y + widget->size.y),
		data.img[0], ivec4(0, 0, data.img[0]->size.x, data.img[0]->size.y));
}

bool ftgr_wdrawer_stretch_img_cpu(t_widget *widget, t_ftgr_img *img)
{
	if (widget == NULL || img == NULL)
		return FALSE;
	ftgr_add_wdrawer(widget, (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)__ftgr_wdrawer_stretch_img_cpu, .data = {.img = {img}}});
	return TRUE;
}



static void __ftgr_wdrawer_copy_img_cpu(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, union u_widget_data data)
{
	ftgr_cpy_img(
		out, ivec2(abs_pos.x, abs_pos.y),
		data.img[0], ivec4(0, 0, data.img[0]->size.x, data.img[0]->size.y));
}

bool ftgr_wdrawer_copy_img_cpu(t_widget *widget, t_ftgr_img *img)
{
	if (widget == NULL || img == NULL)
		return FALSE;
	ftgr_add_wdrawer(widget, (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)__ftgr_wdrawer_copy_img_cpu, .data = {.img = {img}}});
	return TRUE;
}



static void __ftgr_wdrawer_paint_rect(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, union u_widget_data data)
{
	ftgr_fill_rect(out,
				   ivec4(abs_pos.x, abs_pos.y,
						 widget->size.x + abs_pos.x,
						 widget->size.y + abs_pos.y),
				   data.color[0]);
}

bool ftgr_wdrawer_paint_rect(t_widget *widget, t_color color)
{
	if (widget == NULL)
		return FALSE;
	ftgr_add_wdrawer(widget, (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)__ftgr_wdrawer_paint_rect, .data = {.color = {color}}});
	return TRUE;
}



static void __ftgr_wdrawer_draw_rect(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, union u_widget_data data)
{
	ftgr_draw_rect(out,
				   ivec4(abs_pos.x, abs_pos.y,
						 widget->size.x + abs_pos.x,
						 widget->size.y + abs_pos.y),
				   data.color[0]);
}

bool ftgr_wdrawer_draw_rect(t_widget *widget, t_color color)
{
	if (widget == NULL)
		return FALSE;
	ftgr_add_wdrawer(widget, (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)__ftgr_wdrawer_draw_rect, .data = {.color = {color}}});
	return TRUE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 00:44:07 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/09 00:44:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef FT_OS_WIN
#include "libftgr_win_int.h"
#else
#endif

#ifdef FT_OS_WIN
void __ftgr_wdrawer_stretch_img_cpu(t_ftgr_ctx *ctx, t_surface *surface, t_widget *widget, void *data, t_iv4 rect)
{
	t_ftgr_img *img = (t_ftgr_img *)data;
	t_ftgr_img_int *img_int = FTGR_IMAGE_INT(img);
	CHECKRET(StretchBlt(
		surface->dc, widget->pos.x, widget->pos.y, widget->size.x, widget->size.y,
		img_int->dc, 0, 0, img->size.x, img->size.y,
		SRCCOPY));
}

bool ftgr_wdrawer_stretch_img_cpu(t_widget *widget, t_ftgr_img *img)
{
	if (widget == NULL || img == NULL || widget->drawers_n >= (sizeof(widget->drawers) / sizeof(widget->drawers[0])))
		return FALSE;
	widget->drawers[widget->drawers_n++] = (t_widget_drawer){.draw_f = __ftgr_wdrawer_stretch_img_cpu, .data = img};
	return TRUE;
}

void __ftgr_wdrawer_stretch_img_cpu2(t_ftgr_ctx *ctx, t_surface *surface, t_widget *widget, void *data, t_iv4 rect)
{
	t_ftgr_img *img = (t_ftgr_img *)data;
	t_ftgr_img_int *img_int = FTGR_IMAGE_INT(img);
	CHECKRET(StretchBlt(
		surface->dc, widget->pos.x, widget->pos.y, widget->size.x, widget->size.y,
		img_int->dc, 0, 0, img->size.x, img->size.y,
		SRCCOPY));
}

bool ftgr_wdrawer_stretch_img_cpu2(t_widget *widget, t_ftgr_img *img)
{
	if (widget == NULL || img == NULL || widget->drawers_n >= (sizeof(widget->drawers) / sizeof(widget->drawers[0])))
		return FALSE;
	widget->drawers[widget->drawers_n++] = (t_widget_drawer){.draw_f = __ftgr_wdrawer_stretch_img_cpu, .data = img};
	return TRUE;
}

#else

void __ftgr_wdrawer_stretch_img_cpu(t_ftgr_ctx *ctx, t_surface *surface, t_widget *widget, void *data, t_iv4 rect)
{
	t_ftgr_img *img = (t_ftgr_img *)data;

	S32 x_start = ft_imax(rect.x, widget->pos.x);
	S32 y_start = ft_imax(rect.y, widget->pos.y);

	S32 x_end = ft_imin(rect.w, widget->pos.x + widget->size.x);
	S32 y_end = ft_imin(rect.z, widget->pos.y + widget->size.y);

	for (S32 y = y_start; y < y_end; y++)
	{
		F32 ty = (F32)(y - widget->pos.y) / (F32)(widget->size.y);
		for (S32 x = x_start; x < x_end; x++)
		{
			F32 tx = (F32)(x - widget->pos.x) / (F32)(widget->size.x);
			t_color col = ftgr_get_pixel(img, ivec2(
												  tx * img->size.x,
												  ty * img->size.y));
			ftgr_set_pixel(surface, ivec2(x, y), col);
		}
	}
}

bool ftgr_wdrawer_stretch_img_cpu(t_widget *widget, t_ftgr_img *img)
{
	if (widget == NULL || img == NULL || widget->drawers_n >= (sizeof(widget->drawers) / sizeof(widget->drawers[0])))
		return FALSE;
	widget->drawers[widget->drawers_n++] = (t_widget_drawer){.draw_f = __ftgr_wdrawer_stretch_img_cpu, .data = img};
	return TRUE;
}

#endif

t_widget *ftgr_new_widget()
{
	t_widget *widget = malloc(sizeof(t_widget));
	ft_bzero(widget, sizeof(t_widget));
	return widget;
}

void ftgr_add_widget(t_widget *widget, t_widget *master)
{
	widget->master = master;

	if (master->childrens == NULL)
	{
		master->childrens = widget;
		master->last = widget;
	}
	else
	{
		master->last->next = widget;
		master->last = widget;
	}
}

void ftgr_remove_widget(t_widget *widget)
{
	t_widget *master;
	t_widget *w;

	master = widget->master;
	if (UNLIKELY(master == NULL))
		return;
	w = master->childrens;

	if (w == widget)
	{
		if (w == master->last)
			master->last = NULL;
		master->childrens = w->next;
	}
	else
	{
		while (w)
		{
			if (w->next == widget)
			{
				if (w->next == master->last)
					master->last = w;
				w->next = widget->next;
				break;
			}
			w = w->next;
		}
	}
	widget->master = NULL;
}

void ftgr_free_widget(t_widget *widget)
{
	ftgr_remove_widget(widget);
	while (widget->childrens)
	{
		widget->childrens->master = NULL;
		widget->childrens = widget->childrens->next;
	}
	free(widget);
}

static void _ftgr_free_widget_recursive(t_widget *widget)
{
	t_widget *next;

	while (widget->childrens)
	{
		next = widget->childrens->next;
		_ftgr_free_widget_recursive(widget->childrens);
		free(widget->childrens);
		widget->childrens = next;
	}
}

void ftgr_free_widget_recursive(t_widget *widget)
{
	ftgr_remove_widget(widget);
	_ftgr_free_widget_recursive(widget);
	free(widget);
}

void ftgr_draw_widget_recursive(t_ftgr_win *win, t_widget *widget, t_iv4 rect)
{
	t_widget *w;

	ftgr_draw_widget(win, widget, rect);

	w = widget->childrens;
	while (w)
	{
		ftgr_draw_widget(win, w, rect);
		w = w->next;
	}
}

void ftgr_draw_widget(t_ftgr_win *win, t_widget *widget, t_iv4 rect)
{
	for (U8 i = 0; i < widget->drawers_n; i++)
		widget->drawers[i].draw_f(win->ctx, (t_surface *)win, widget, widget->drawers[i].data, rect);
}

void ftgr_move_widget(t_ftgr_win *win, t_widget *widget, t_v2 pos)
{
	t_v2 old_pos = widget->pos;
	widget->pos = pos;

	t_iv4 rect = {
		.x = old_pos.x,
		.y = old_pos.y,
		.z = old_pos.x + widget->size.x,
		.w = old_pos.y + widget->size.y};
	ftgr_redraw_rect(win, rect);

	rect.z = pos.x + widget->size.x;
	rect.w = pos.y + widget->size.y;
	ftgr_redraw_rect(win, rect);
}

void ftgr_resize_widget(t_ftgr_win *win, t_widget *widget, t_v2 size)
{
	t_iv4 rect = {
		.x = widget->pos.x,
		.y = widget->pos.y,
		.z = widget->pos.x + widget->size.x,
		.w = widget->pos.y + widget->size.y};
	ftgr_redraw_rect(win, rect);

	widget->size = size;
	rect.z = widget->pos.x + widget->size.x;
	rect.w = widget->pos.y + widget->size.y;
	ftgr_redraw_rect(win, rect);
}

void ftgr_redraw_rect(t_ftgr_win *win, t_iv4 rect)
{
	RECT r;

	r = (RECT){
		.left = rect.x,
		.top = rect.y,

		.right = rect.z,
		.bottom = rect.w};
	CHECKRET(InvalidateRect(win->window_handle, &r, TRUE));
//	UpdateWindow(win->window_handle);
}

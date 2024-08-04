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

#include "libft/std.h"

#ifdef FT_OS_WIN
#include "libftgr_win_int.h"
#else
#include "libftgr_x11_int.h"
#endif

static void __ftgr_wdrawer_stretch_img_cpu(t_ftgr_img *out, t_widget *widget, void *data);
static void __ftgr_wdrawer_paint_rect(t_ftgr_img *out, t_widget *widget, void *data);

t_widget *ftgr_new_widget()
{
	t_widget *widget = malloc(sizeof(t_widget));
	if (widget == NULL)
		return NULL;
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

void ftgr_draw_widget_recursive(t_ftgr_img *out, t_widget *widget)
{
	ftgr_draw_widget(out, widget);
	for (t_widget *w = widget->childrens; w; w = w->next)
		ftgr_draw_widget(out, w);
}

void ftgr_draw_widget(t_ftgr_img *out, t_widget *widget)
{
	for (U8 i = 0; i < widget->drawers_n; i++)
		widget->drawers[i].draw_f(out, widget, widget->drawers[i].data);
}

/*
WIDGETS DRAWERS
*/
static void __ftgr_wdrawer_stretch_img_cpu(t_ftgr_img *out, t_widget *widget, void *data)
{
	t_ftgr_img *img = (t_ftgr_img *)data;

	ftgr_stretch_img(
		out, ivec4(widget->pos.x, widget->pos.y, widget->pos.x + widget->size.x, widget->pos.y + widget->size.y),
		img, ivec4(0, 0, img->size.x, img->size.y));
}

bool ftgr_wdrawer_stretch_img_cpu(t_widget *widget, t_ftgr_img *img)
{
	if (widget == NULL || img == NULL || widget->drawers_n >= (sizeof(widget->drawers) / sizeof(widget->drawers[0])))
		return FALSE;
	widget->drawers[widget->drawers_n++] = (t_widget_drawer){.draw_f = __ftgr_wdrawer_stretch_img_cpu, .data = img};
	return TRUE;
}


static void __ftgr_wdrawer_paint_rect(t_ftgr_img *out, t_widget *widget, void *data)
{
	t_color *color = (t_color *)data;
	ftgr_fill_rect(out,
		ivec4(widget->pos.x, widget->pos.y,
		widget->size.x + widget->pos.x,
		widget->size.y + widget->pos.y),
		*color);
}

bool ftgr_wdrawer_paint_rect(t_widget *widget, t_color *color)
{
	if (widget == NULL || color == NULL || widget->drawers_n >= (sizeof(widget->drawers) / sizeof(widget->drawers[0])))
		return FALSE;
	widget->drawers[widget->drawers_n++] = (t_widget_drawer){.draw_f = __ftgr_wdrawer_paint_rect, .data = color};
	return TRUE;
}

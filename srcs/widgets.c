/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 00:44:07 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/02 03:21:10 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"

#ifdef FT_OS_WIN
#include "libftgr_win_int.h"
#else
#include "libftgr_x11_int.h"
#endif

t_widget *ftgr_new_widget()
{
	t_widget *widget = malloc(sizeof(t_widget));
	if (widget == NULL)
		return NULL;
	ftgr_init_widget(widget);
	return widget;
}

void ftgr_init_widget(t_widget *widget)
{
	ft_bzero(widget, sizeof(t_widget));
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
	for (U8 i = 0; i < widget->drawers_n; i++)
		if (widget->drawers[i].cleanup_data)
			free(widget->drawers[i].data);
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
	for (U8 i = 0; i < widget->drawers_n; i++)
		if (widget->drawers[i].cleanup_data)
			free(widget->drawers[i].data);
	free(widget);
}

static void ftgr_handle_widget_events_rec(t_ftgr_ctx *ctx, t_widget *w, t_iv2 mouse_pos)
{
	if (w->handle_input)
	{
		bool is_mouse_in = (mouse_pos.x >= w->pos.x && mouse_pos.y >= w->pos.y &&
							mouse_pos.x <= w->pos.x + w->size.x && mouse_pos.y <= w->pos.y + w->size.y);

		if (is_mouse_in)
		{
			if (!w->hovered)
			{
				w->hovered = TRUE;
				if (w->on_cursor_enter)
					w->on_cursor_enter(w, mouse_pos);
			}
			else
			{
				if (w->on_cursor_move)
					w->on_cursor_move(w, mouse_pos);
			}

			if (ftgr_mouse_pressed(ctx, MOUSE_LEFT) && LIKELY(!w->clicked))
			{
				w->clicked = TRUE;
				if (w->on_cursor_click)
					w->on_cursor_click(w, mouse_pos);
			}
		}
		else if (w->hovered)
		{
			w->hovered = FALSE;
			if (w->on_cursor_exit)
				w->on_cursor_exit(w, mouse_pos);
		}

		if (w->clicked && ftgr_mouse_released(ctx, MOUSE_LEFT))
		{
			w->clicked = FALSE;
			if (w->on_cursor_release)
				w->on_cursor_release(w, mouse_pos);
		}
	}
	for (t_widget *c = w->childrens; c; c = c->next)
		ftgr_handle_widget_events_rec(ctx, c, mouse_pos);
}

void ftgr_handle_widget_events(t_ftgr_win *win, t_widget *w)
{
	t_iv2 mouse_pos = ftgr_mouse_get_pos(win->ctx, win);
	ftgr_handle_widget_events_rec(win->ctx, w, mouse_pos);
}

void ftgr_draw_widget_recursive(t_ftgr_img *out, t_widget *widget)
{
	ftgr_draw_widget(out, widget);
	for (t_widget *w = widget->childrens; w; w = w->next)
		ftgr_draw_widget_recursive(out, w);
}

void ftgr_draw_widget(t_ftgr_img *out, t_widget *widget)
{
	for (U8 i = 0; i < widget->drawers_n; i++)
		widget->drawers[i].draw_f(out, widget, widget->drawers[i].data);
}

/*
WIDGETS DRAWERS
*/
static void __ftgr_wdrawer_stretch_img_cpu(t_ftgr_img *out, t_widget *widget, t_ftgr_img *img)
{
	ftgr_stretch_img(
		out, ivec4(widget->pos.x, widget->pos.y, widget->pos.x + widget->size.x, widget->pos.y + widget->size.y),
		img, ivec4(0, 0, img->size.x, img->size.y));
}

bool ftgr_wdrawer_stretch_img_cpu(t_widget *widget, t_ftgr_img *img)
{
	if (widget == NULL || img == NULL || widget->drawers_n >= (sizeof(widget->drawers) / sizeof(widget->drawers[0])))
		return FALSE;
	widget->drawers[widget->drawers_n++] = (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)__ftgr_wdrawer_stretch_img_cpu, .data = img, .cleanup_data = FALSE};
	return TRUE;
}

static void __ftgr_wdrawer_copy_img_cpu(t_ftgr_img *out, t_widget *widget, t_ftgr_img *img)
{
	ftgr_cpy_img(
		out, ivec2(widget->pos.x, widget->pos.y),
		img, ivec4(0, 0, img->size.x, img->size.y));
}

bool ftgr_wdrawer_copy_img_cpu(t_widget *widget, t_ftgr_img *img)
{
	if (widget == NULL || img == NULL || widget->drawers_n >= (sizeof(widget->drawers) / sizeof(widget->drawers[0])))
		return FALSE;
	widget->drawers[widget->drawers_n++] = (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)__ftgr_wdrawer_copy_img_cpu, .data = img, .cleanup_data = FALSE};
	return TRUE;
}

static void __ftgr_wdrawer_paint_rect(t_ftgr_img *out, t_widget *widget, t_color *color)
{
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
	widget->drawers[widget->drawers_n++] = (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)__ftgr_wdrawer_paint_rect, .data = color, .cleanup_data = FALSE};
	return TRUE;
}

static void __ftgr_wdrawer_draw_bitmap_text(t_ftgr_img *out, t_widget *widget, t_bitmap_text_infos *infos)
{
	ftgr_draw_bitmap_text(out, ivec4(widget->pos.x, widget->pos.y, widget->size.x + widget->pos.x, widget->size.y + widget->pos.y),
						  *infos);
}

bool ftgr_wdrawer_bitmap_text(t_widget *widget, t_bitmap_text_infos *infos)
{
	if (widget == NULL || infos == NULL || widget->drawers_n >= (sizeof(widget->drawers) / sizeof(widget->drawers[0])))
		return FALSE;
	widget->drawers[widget->drawers_n++] = (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)__ftgr_wdrawer_draw_bitmap_text, .data = infos, .cleanup_data = FALSE};
	return TRUE;
}



t_label_widget *ftgr_label_widget(t_bitmap *bitmap)
{
	t_label_widget *label = malloc(sizeof(t_label_widget));
	if (label == NULL)
		return NULL;
	ft_bzero(label, sizeof(t_label_widget));

	label->infos.bitmap = bitmap;
	label->infos.kerning = ivec2(2, 2);
	label->infos.scale = 2;
	label->infos.text = "";

	ftgr_wdrawer_bitmap_text((t_widget *)label, &label->infos);

	return label;
}

void ftgr_label_update(t_label_widget *label, string text)
{
	label->infos.text = text;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 00:44:07 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/21 01:09:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#include "libft/limits.h"

#ifdef FT_OS_WIN
#include "libftgr_win_int.h"
#else
#include "libftgr_x11_int.h"
#endif

#pragma region "Widget new/free"
t_widget *ftgr_new_widget()
{
	t_widget *widget = malloc(sizeof(t_widget));
	if (widget == NULL || ftgr_init_widget(widget) == FALSE)
	{
		free(widget);
		return NULL;
	}
	return widget;
}

bool ftgr_init_widget(t_widget *widget)
{
	const U64 widget_init_drawers_alloc = 4;

	ft_bzero(widget, sizeof(t_widget));
	if ((widget->drawers = malloc(sizeof(t_widget_drawer) * widget_init_drawers_alloc)) == NULL)
		return FALSE;
	widget->drawers_alloc = widget_init_drawers_alloc;
	return TRUE;
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

bool ftgr_add_wdrawer(t_widget *widget, t_widget_drawer drawer)
{
	if (widget->drawers_n >= widget->drawers_alloc)
	{
		void *new = malloc(sizeof(t_widget_drawer) * widget->drawers_n * 2);
		if (UNLIKELY(new == NULL))
			return FALSE;
		ft_memcpy(new, widget->drawers, sizeof(t_widget_drawer) * widget->drawers_n);
		free(widget->drawers);
		widget->drawers = new;
		widget->drawers_alloc = widget->drawers_n * 2;
	}

	widget->drawers[widget->drawers_n++] = drawer;
	return TRUE;
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
#pragma endregion

t_iv2 ftgr_widget_abs_pos(t_widget *widget)
{
	t_iv2 pos = widget->pos;

	while (widget->master)
	{
		widget = widget->master;
		pos = ivec2_add(pos, widget->pos);
	}

	return pos;
}

#pragma region "Widget events"
static void ftgr_handle_widget_events_rec(t_ftgr_ctx *ctx, t_widget *w, t_iv2 mouse_pos, t_iv2 ofs)
{
	t_iv2 pos = ivec2_add(ofs, w->pos);

	if (w->handle_input)
	{
		bool is_mouse_in = (mouse_pos.x >= pos.x && mouse_pos.y >= pos.y &&
							mouse_pos.x <= pos.x + w->size.x && mouse_pos.y <= pos.y + w->size.y);

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
		ftgr_handle_widget_events_rec(ctx, c, mouse_pos, pos);
}

void ftgr_handle_widget_events(t_ftgr_win *win, t_widget *w)
{
	t_iv2 mouse_pos = ftgr_mouse_get_pos(win->ctx, win);
	ftgr_handle_widget_events_rec(win->ctx, w, mouse_pos, ivec2(0, 0));
}
#pragma endregion

#pragma region "Widget draw"
void ftgr_draw_widget_recursive(t_ftgr_img *out, t_widget *widget)
{
	ftgr_draw_widget(out, widget);
	for (t_widget *w = widget->childrens; w; w = w->next)
		ftgr_draw_widget_recursive(out, w);
}

void ftgr_draw_widget(t_ftgr_img *out, t_widget *widget)
{
	t_iv2 abs_pos = ftgr_widget_abs_pos(widget);
	for (U8 i = 0; i < widget->drawers_n; i++)
		widget->drawers[i].draw_f(out, widget, abs_pos, widget->drawers[i].data);
}
#pragma endregion

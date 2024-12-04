/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 00:44:07 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/03 22:06:41 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _FT_RETURN 1

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
	t_widget *widget;

	if (UNLIKELY((widget = malloc(sizeof(t_widget))) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	if (ftgr_init_widget(widget) == FALSE)
		return NULL;
	FT_RET_OK(widget);
}

bool ftgr_init_widget(t_widget *widget)
{
	const U64 widget_init_childrens_alloc = 4;
	const U64 widget_init_drawers_alloc = 4;

	ft_bzero(widget, sizeof(t_widget));

	if ((widget->drawers = malloc(sizeof(t_widget_drawer) * widget_init_drawers_alloc)) == NULL)
		FT_RET_ERR(FALSE, FT_EOMEM);
	widget->drawers_alloc = widget_init_drawers_alloc;

	if ((widget->childrens = malloc(sizeof(t_widget_drawer) * widget_init_childrens_alloc)) == FALSE)
	{
		free(widget->drawers);
		FT_RET_ERR(FALSE, FT_EOMEM);
	}
	widget->childrens_alloc = widget_init_childrens_alloc;

	FT_RET_OK(TRUE);
}

static void _widget_childrens_compact(t_widget *widget)
{
	U64 i, j;
	U64 free_len;
	U64 len;

	i = 0;
	j = 0;
	while (i < widget->childrens_n)
	{
		if (widget->childrens[i] != NULL)
		{
			i++;
			continue;
		}

		j = i;
		while (widget->childrens[j] == NULL)
			j++;
		len = 0;
		while (widget->childrens[j + len] != NULL && len < free_len)
			len++;
		ft_memcpy(&widget->childrens[i], &widget->childrens[j], sizeof(t_widget *) * len);
		for (; (j - i) < len; j++, i++)
			widget->childrens[j]->master_i = j;
	}
	widget->childrens_del = 0;
}

bool ftgr_add_widget(t_widget *widget, t_widget *master)
{
	void *new;

	if (widget->childrens_n >= widget->childrens_alloc)
	{
		if (UNLIKELY((new = malloc(sizeof(t_widget *) * widget->childrens_n * 2)) == NULL))
			FT_RET_ERR(FALSE, FT_EOMEM);
		ft_memcpy(new, widget->childrens, sizeof(t_widget *) * widget->childrens_n);
		free(widget->childrens);
		widget->childrens = new;
		widget->childrens_alloc = widget->childrens_n * 2;
	}

	widget->master = master;
	master->childrens[master->childrens_n] = widget;
	widget->master_i = master->childrens_n;
	master->childrens_n++;
	FT_RET_OK(FALSE);
}

void ftgr_remove_widget(t_widget *widget)
{
	t_widget *master;

	master = widget->master;
	if (widget == master->childrens[master->childrens_n])
	{
		master->childrens_n--;
		return;
	}

	ft_memcpy(&master->childrens[widget->master_i], &master->childrens[widget->master_i + 1], master->childrens_n - widget->master_i - 1);
	master->childrens_n--;
	widget->master = NULL;
}

void ftgr_free_widget(t_widget *widget)
{
	ftgr_remove_widget(widget);
	for (U64 i = 0; i < widget->childrens_n; i++)
	{
		widget->childrens[i]->master = NULL;
		widget->childrens[i]->master_i = 0;
	}
	free(widget->childrens);
	free(widget->drawers);
	free(widget);
}

bool ftgr_add_wdrawer(t_widget *widget, t_widget_drawer drawer)
{
	if (widget->drawers_n >= widget->drawers_alloc)
	{
		void *new = malloc(sizeof(t_widget_drawer) * widget->drawers_n * 2);
		if (UNLIKELY(new == NULL))
			FT_RET_ERR(FALSE, FT_EOMEM);
		ft_memcpy(new, widget->drawers, sizeof(t_widget_drawer) * widget->drawers_n);
		free(widget->drawers);
		widget->drawers = new;
		widget->drawers_alloc = widget->drawers_n * 2;
	}

	widget->drawers[widget->drawers_n++] = drawer;
	FT_RET_OK(TRUE);
}

static void _ftgr_free_widget_recursive(t_widget *widget)
{
	for (U64 i = 0; i < widget->childrens_n; i++)
	{
		_ftgr_free_widget_recursive(widget->childrens[i]);
		ftgr_free_widget(widget);
	}
}

void ftgr_free_widget_recursive(t_widget *widget)
{
	ftgr_remove_widget(widget);
	_ftgr_free_widget_recursive(widget);
	ftgr_free_widget(widget);
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
	
	for (U64 i = 0; i < w->childrens_n; i++)
		ftgr_handle_widget_events_rec(ctx, w->childrens[i], mouse_pos, pos);
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
	for (U64 i = 0; i < widget->childrens_n; i++)
		ftgr_draw_widget_recursive(out, widget->childrens[i]);
}

void ftgr_draw_widget(t_ftgr_img *out, t_widget *widget)
{
	t_iv2 abs_pos = ftgr_widget_abs_pos(widget);
	for (U8 i = 0; i < widget->drawers_n; i++)
		widget->drawers[i].draw_f(out, widget, abs_pos, widget->drawers[i].data);
}
#pragma endregion

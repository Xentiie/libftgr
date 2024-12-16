/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:09:01 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/12 16:02:49 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _FT_RETURN
#include "widgets2.h"
#include "libftgr.h"

#include "libft/limits.h"

#include <stdlib.h>

#pragma warning "test"
#if defined(WIDGETS2_H)

t_widget *ftgr_new_widget()
{
	t_widget *widget;

	if (UNLIKELY((widget = malloc(sizeof(t_widget))) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	if (ftgr_init_widget(widget) == FALSE)
	{
		free(widget);
		return NULL;
	}
	FT_RET_OK(widget);
}

bool ftgr_init_widget(t_widget *widget)
{
	// __attribute__((note("tunable")))
	const U64 widget_init_childrens_alloc = 4;

	ft_bzero(widget, sizeof(t_widget));

	if ((widget->childrens = malloc(sizeof(t_widget *) * widget_init_childrens_alloc)) == FALSE)
		FT_RET_ERR(FALSE, FT_EOMEM);

	widget->childrens_alloc = widget_init_childrens_alloc;

	widget->damage = ivec4(S32_MAX, S32_MAX, S32_MIN, S32_MIN);

	FT_RET_OK(TRUE);
}

void ftgr_free_widget(t_widget *widget)
{
	free(widget->childrens);
	free(widget);
}

static void __free_widget_recursive(t_widget *widget)
{
	for (U64 i = 0; i < widget->childrens_n; i++)
	{
		__free_widget_recursive(widget->childrens[i]);
		ftgr_free_widget(widget);
	}
}

void ftgr_free_widget_recursive(t_widget *widget)
{
	ftgr_remove_widget(widget);
	__free_widget_recursive(widget);
	ftgr_free_widget(widget);
}

bool ftgr_add_widget(t_widget *widget, t_widget *master)
{
	void *new;

	if (master->childrens_n >= master->childrens_alloc)
	{
		if (UNLIKELY((new = malloc(sizeof(t_widget *) * master->childrens_n * 2)) == NULL))
			FT_RET_ERR(FALSE, FT_EOMEM);
		ft_memcpy(new, master->childrens, sizeof(t_widget *) * master->childrens_n);
		free(master->childrens);
		master->childrens = new;
		master->childrens_alloc = master->childrens_n * 2;
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

void _ftgr_update_widgets(struct s_widget_root *root_data, t_widget *w, t_iv2 ofs, t_iv2 mouse_pos)
{
	t_ftgr_widget_ev ev;
	bool prev_mouse_in;
	bool mouse_in;
	t_iv2 pos;

	pos = ivec2_add(ofs, w->pos);
	mouse_in = (mouse_pos.x >= pos.x && mouse_pos.y >= pos.y &&
				mouse_pos.x <= pos.x + w->size.x && mouse_pos.y <= pos.y + w->size.y);
	prev_mouse_in = (root_data->last_mouse_pos.x >= pos.x && root_data->last_mouse_pos.y >= pos.y &&
					 root_data->last_mouse_pos.x <= pos.x + w->size.x && root_data->last_mouse_pos.y <= pos.y + w->size.y);

	if (prev_mouse_in && !mouse_in)
	{
		ev.type = FTGR_WIDGET_EV_CURSOR_EXIT;
		w->widget_proc(w, ev);
	}
	else if (mouse_in)
	{
		if (!prev_mouse_in)
		{
			ev.type = FTGR_WIDGET_EV_CURSOR_ENTER;
			w->widget_proc(w, ev);
		}

		if (mouse_pos.x != root_data->last_mouse_pos.x || mouse_pos.y != root_data->last_mouse_pos.y)
		{
			ev.type = FTGR_WIDGET_EV_CURSOR_MOVE;
			w->widget_proc(w, ev);
		}
	}

	for (U64 i = 0; i < w->childrens_n; i++)
		_ftgr_update_widgets(root_data, w->childrens[i], mouse_pos);
}

void ftgr_update_widgets(t_ftgr_win *win, struct s_widget_root *root_data, t_widget *root)
{
	t_iv2 mouse_pos;

	mouse_pos = ftgr_mouse_get_pos(win->ctx, win);
	_ftgr_update_widgets(root_data, root, ivec2(0, 0), mouse_pos);
	root_data->last_mouse_pos = mouse_pos;
}

#endif
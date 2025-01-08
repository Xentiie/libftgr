/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:09:01 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/27 14:59:33 by reclaire         ###   ########.fr       */
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

#define MOUSE_EVENTS_MOVE_MASK_OFS 0
#define MOUSE_EVENTS_ENTER_MASK_OFS 1
#define MOUSE_EVENTS_EXIT_MASK_OFS 2
#define MOUSE_EVENTS_CLICK_MASK_OFS 3
#define MOUSE_EVENTS_RELEASE_MASK_OFS 4

#define MOUSE_EVENTS_MOVE_MASK (1 << MOUSE_EVENTS_MOVE_MASK_OFS)
#define MOUSE_EVENTS_ENTER_MASK (1 << MOUSE_EVENTS_ENTER_MASK_OFS)
#define MOUSE_EVENTS_EXIT_MASK (1 << MOUSE_EVENTS_EXIT_MASK_OFS)
#define MOUSE_EVENTS_CLICK_MASK (1 << MOUSE_EVENTS_CLICK_MASK_OFS)
#define MOUSE_EVENTS_RELEASE_MASK (1 << MOUSE_EVENTS_RELEASE_MASK_OFS)

#define call_proc_update_mask(w, ev, mask_ofs) mask &= (w->widget_proc(w, ev) << mask_ofs)

static void do_mouse_events(t_widget *w, t_iv2 last_mouse_pos, t_iv2 mouse_pos, t_iv2 ofs, U8 mask)
{
	t_ftgr_ev ev;			/* event to send */
	bool prev_mouse_in;		/* is previous mouse pos in widget w */
	bool mouse_in;			/* is current mouse pos in widget w */
	t_iv2 ofs_pos; /* ofs + w->pos */

	ofs_pos = ivec2_add(ofs, w->pos);
	mouse_in = (mouse_pos.x >= ofs_pos.x && mouse_pos.y >= ofs_pos.y &&
				mouse_pos.x <= ofs_pos.x + w->size.x && mouse_pos.y <= ofs_pos.y + w->size.y);
	prev_mouse_in = (last_mouse_pos.x >= ofs_pos.x && last_mouse_pos.y >= ofs_pos.y &&
					 last_mouse_pos.x <= ofs_pos.x + w->size.x && last_mouse_pos.y <= ofs_pos.y + w->size.y);

	if ((mask & MOUSE_EVENTS_EXIT_MASK) && prev_mouse_in && !mouse_in)
	{
		ev.type = FTGR_MOUSE_EXIT;
		ev.mouse_exit.pos = mouse_pos;
		call_proc_update_mask(w, ev, MOUSE_EVENTS_EXIT_MASK_OFS);
	}
	else if (mouse_in)
	{
		if ((mask & MOUSE_EVENTS_ENTER_MASK) && !prev_mouse_in)
		{
			ev.type = FTGR_MOUSE_ENTER;
			ev.mouse_enter.pos = mouse_pos;
			call_proc_update_mask(w, ev, MOUSE_EVENTS_ENTER_MASK_OFS);
		}

		if ((mask & MOUSE_EVENTS_MOVE_MASK) && (mouse_pos.x != last_mouse_pos.x || mouse_pos.y != last_mouse_pos.y))
		{
			ev.type = FTGR_MOUSE_MOVE;
			ev.mouse_move.pos = mouse_pos;
			call_proc_update_mask(w, ev, MOUSE_EVENTS_MOVE_MASK_OFS);
		}
	}

	for (U64 i = 0; i < w->childrens_n; i++)
		do_mouse_events(w->childrens[i], last_mouse_pos, mouse_pos, ofs_pos, mask);
}

void ftgr_update_widgets(t_ftgr_win *win, t_widget *root)
{
	t_iv2 mouse_pos;

	mouse_pos = ftgr_mouse_get_pos(win->ctx, win);
	do_mouse_events(root, win->last_mouse_pos, mouse_pos, ivec2(0, 0), 0xFFFF);
	win->last_mouse_pos = mouse_pos;
}

void ftgr_draw_widgets(t_ftgr_win *win, t_widget *root)
{
	t_ftgr_ev ev;

	if (win->damage.x > win->damage.z)
		return;

	ev.type = FTGR_EXPOSE;
	ev.expose.win = win;
	ev.expose.rect = win->damage;
}

#endif
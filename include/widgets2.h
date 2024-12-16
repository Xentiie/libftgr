/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:04:00 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/12 16:06:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(WIDGETS2_H) && !defined(WIDGETS_H)
#define WIDGETS2_H

#include "libftgr.h"

#define FTGR_WIDGET_EV_EXPOSE 1
#define FTGR_WIDGET_EV_CURSOR_ENTER 2
#define FTGR_WIDGET_EV_CURSOR_EXIT 3
#define FTGR_WIDGET_EV_CURSOR_MOVE 4
#define FTGR_WIDGET_EV_CURSOR_CLICK 5
#define FTGR_WIDGET_EV_CURSOR_RELEASE 6

typedef struct s_ftgr_widget_ev
{
	S32 type;

	union
	{
		struct
		{
			t_iv2 mouse_pos;
			t_iv2 last_mouse_pos;
		} mouse_event;

		struct
		{
			t_iv4 rect;
		} expose_event;
	};
} t_ftgr_widget_ev;

typedef struct s_widget
{
	t_iv2 pos;
	t_iv2 size;

	/*
	widget procedure: handle events
	returns TRUE if event should be passed down to childrens, FALSE otherwise
	*/
	bool (*widget_proc)(t_widget *w, t_ftgr_widget_ev ev);

	/* ptr to master */
	struct s_widget *master;
	/* index in master->childrens */
	U64 master_i;

	/* optional, can be NULL */
	string name;

	void *data;

	U64 childrens_n;
	U64 childrens_del;
	U64 childrens_alloc;
	struct s_widget **childrens;

	t_iv4 damage;
} t_widget;

struct s_widget_root
{
	U64 events_n;
	U64 events_alloc;
	t_ftgr_widget_ev *events;
	t_iv2 last_mouse_pos;
};

t_widget *ftgr_new_widget();
bool ftgr_init_widget(t_widget *widget);
void ftgr_free_widget_recursive(t_widget *widget);
void ftgr_free_widget(t_widget *widget);

bool ftgr_add_widget(t_widget *widget, t_widget *master);
void ftgr_remove_widget(t_widget *widget);

t_iv2 ftgr_widget_abs_pos(t_widget *widget);
t_iv4 ftgr_widget_rect(t_widget *widget);

t_widget *ftgr_widget_iter(t_widget **widget);

#endif

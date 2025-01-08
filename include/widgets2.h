/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:04:00 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/27 00:41:27 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(WIDGETS2_H) && !defined(WIDGETS_H)
#define WIDGETS2_H

#include "libftgr.h"

typedef struct s_widget
{
	t_iv2 pos;
	t_iv2 size;

	/*
	widget procedure: handle events
	returns TRUE if event should be passed down to childrens, FALSE otherwise
	*/
	bool (*widget_proc)(t_widget *w, t_ftgr_ev ev);

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
} t_widget;

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

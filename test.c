/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:40:24 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/27 00:18:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widgets2.h"
#include "libftgr.h"

#include "libft/time.h"
#include "libft/io.h"

#include <stdlib.h>
#include <stdio.h>

void default_widget_proc(t_widget *w, t_ftgr_widget_ev ev)
{
	switch (ev.type)
	{
	case FTGR_WIDGET_EV_EXPOSE:
		ftgr_draw_rect2();
		break;
	}
}

S32 main()
{
	t_ftgr_ctx *ctx;
	t_ftgr_win *win;

	ctx = ftgr_create_ctx();
	win = ftgr_new_window(ctx, ivec2(400, 400), "widget stress test");
	win->w_root->name = "root";

	t_widget *widget = ftgr_new_widget();
	widget->pos = ivec2(40, 30);
	widget->size = ivec2(100, 100);
	widget->widget_proc = default_widget_proc;
	ftgr_add_widget(widget, win->w_root);

}

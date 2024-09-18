/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:17:29 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/12 16:35:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/io.h"
#include <stdlib.h>

#define DOTS_RADIUS 2
#define MOVE_HANDLE_SIZE 20

extern t_text debug_text;

static void widget_casing_drawer(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, union u_widget_drawer_data data)
{
	(void)data;
	t_iv4 rect = ivec4(abs_pos.x, abs_pos.y, abs_pos.x + widget->size.x, abs_pos.y + widget->size.y);
	ftgr_draw_rect(out, rect, COL_BLACK);
}

static void widget_size_handle_drawer(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, union u_widget_drawer_data data)
{
	(void)data;
	t_color col = COL_BLACK;
	if (widget->hovered)
		col = COL_GRAY;
	if (widget->clicked)
		col = COL_RED;
	ftgr_draw_disc(out, ivec2_add(abs_pos, ivec2(DOTS_RADIUS * 2, DOTS_RADIUS * 2)), DOTS_RADIUS, col);
	ftgr_draw_rect(out, ivec4(abs_pos.x, abs_pos.y, abs_pos.x + widget->size.x, abs_pos.y + widget->size.y), COL_RED);
}

static void widget_move_handle_drawer(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, union u_widget_drawer_data data)
{
	(void)data;
	ftgr_fill_rect(out, ivec4(abs_pos.x, abs_pos.y, abs_pos.x + widget->size.x, abs_pos.y + widget->size.y), COL_LIGHT_BLUE);
	ftgr_draw_rect(out, ivec4(abs_pos.x, abs_pos.y, abs_pos.x + widget->size.x, abs_pos.y + widget->size.y), COL_BLUE);
}

static void update_handles_pos(t_widget *rect, t_widget *target)
{
	t_widget *w;

	w = rect->childrens;

	w->pos = ivec2(-DOTS_RADIUS * 2, -DOTS_RADIUS * 2);
	w = w->next;

	w->pos = ivec2(target->size.x - DOTS_RADIUS * 2, -DOTS_RADIUS * 2);
	w = w->next;

	w->pos = ivec2(-DOTS_RADIUS * 2, target->size.y - DOTS_RADIUS * 2);
	w = w->next;

	w->pos = ivec2(target->size.x - DOTS_RADIUS * 2, target->size.y - DOTS_RADIUS * 2);
	w = w->next;
}

static bool handle_resize_ul(t_widget *widget, t_iv2 cursor_pos)
{
	t_iv2 old_pos = *((t_iv2 *)(&widget->data));
	t_widget *target = widget->master->master;
	if (widget->clicked)
	{
		target->pos = ivec2_add(target->pos, ivec2_sub(cursor_pos, old_pos));
		target->size = ivec2_sub(target->size, ivec2_sub(cursor_pos, old_pos));
		widget->master->size = target->size;
		widget->data = *((void **)(&cursor_pos));

		update_handles_pos(widget->master, target);
	}
	return TRUE;
}

static bool handle_resize_ur(t_widget *widget, t_iv2 cursor_pos)
{
	t_iv2 old_pos = *((t_iv2 *)(&widget->data));
	t_iv2 dlt = ivec2_sub(cursor_pos, old_pos);
	t_widget *target = widget->master->master;
	if (widget->clicked)
	{
		target->pos = ivec2(target->pos.x, target->pos.y + dlt.y);
		target->size = ivec2(target->size.x + dlt.x, target->size.y - dlt.y);
		widget->master->size = target->size;
		widget->data = *((void **)(&cursor_pos));

		update_handles_pos(widget->master, target);
	}
	return TRUE;
}

static bool handle_resize_ll(t_widget *widget, t_iv2 cursor_pos)
{
	t_iv2 old_pos = *((t_iv2 *)(&widget->data));
	t_iv2 dlt = ivec2_sub(cursor_pos, old_pos);
	t_widget *target = widget->master->master;
	if (widget->clicked)
	{
		target->pos = ivec2(target->pos.x + dlt.x, target->pos.y);
		target->size = ivec2(target->size.x - dlt.x, target->size.y + dlt.y);
		widget->master->size = target->size;
		widget->data = *((void **)(&cursor_pos));

		update_handles_pos(widget->master, target);
	}
	return TRUE;
}

static bool handle_resize_lr(t_widget *widget, t_iv2 cursor_pos)
{
	t_iv2 old_pos = *((t_iv2 *)(&widget->data));
	t_iv2 dlt = ivec2_sub(cursor_pos, old_pos);
	t_widget *target = widget->master->master;
	if (widget->clicked)
	{
		target->pos = ivec2(target->pos.x, target->pos.y);
		target->size = ivec2(target->size.x + dlt.x, target->size.y + dlt.y);
		widget->master->size = target->size;
		widget->data = *((void **)(&cursor_pos));

		update_handles_pos(widget->master, target);
	}
	return TRUE;
}

static bool handle_click(t_widget *widget, t_iv2 cursor_pos)
{
	/* Start drag */
	widget->data = *((void **)(&cursor_pos));
	return TRUE;
}

static bool handle_exit(t_widget *widget, t_iv2 cursor_pos)
{
	if (widget->clicked && widget->on_cursor_move)
		widget->on_cursor_move(widget, cursor_pos);
	return TRUE;
}

void create_widget_editor(t_widget *root)
{
	t_widget *rect, *ul, *ur, *ll, *lr, *move_handle;

	for (t_widget *w = root->childrens; w; w = w->next)
	{
		create_widget_editor(w);

		rect = NULL;
		ul = NULL;
		ur = NULL;
		ll = NULL;
		lr = NULL;
		move_handle = NULL;

		if (
			(rect = ftgr_new_widget()) == NULL ||
			(ul = ftgr_new_widget()) == NULL ||
			(ur = ftgr_new_widget()) == NULL ||
			(ll = ftgr_new_widget()) == NULL ||
			(lr = ftgr_new_widget()) == NULL ||
			(move_handle = ftgr_new_widget()) == NULL)
		{
			free(rect);
			free(ul);
			free(ur);
			free(ll);
			free(lr);
			free(move_handle);
			return;
		}

		rect->name = "Rect";
		rect->pos = ivec2(0, 0);
		rect->size = w->size;
		ftgr_add_wdrawer(rect, (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)widget_casing_drawer});
		rect->data = w;

		ul->name = "Upper left corner handle";
		ul->pos = ivec2(-DOTS_RADIUS * 2, -DOTS_RADIUS * 2);
		ul->size = ivec2(DOTS_RADIUS * 2 * 2, DOTS_RADIUS * 2 * 2);
		ftgr_add_wdrawer(ul, (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)widget_size_handle_drawer});
		ul->handle_input = TRUE;
		ul->on_cursor_exit = handle_exit;
		ul->on_cursor_click = handle_click;
		ul->on_cursor_move = handle_resize_ul;

		ur->name = "Upper right corner handle";
		ur->pos = ivec2(w->size.x - DOTS_RADIUS * 2, -DOTS_RADIUS * 2);
		ur->size = ivec2(DOTS_RADIUS * 2 * 2, DOTS_RADIUS * 2 * 2);
		ftgr_add_wdrawer(ur, (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)widget_size_handle_drawer});
		ur->handle_input = TRUE;
		ur->on_cursor_exit = handle_exit;
		ur->on_cursor_click = handle_click;
		ur->on_cursor_move = handle_resize_ur;

		ll->name = "Lower left corner handle";
		ll->pos = ivec2(-DOTS_RADIUS * 2, w->size.y - DOTS_RADIUS * 2);
		ll->size = ivec2(DOTS_RADIUS * 2 * 2, DOTS_RADIUS * 2 * 2);
		ftgr_add_wdrawer(ll, (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)widget_size_handle_drawer});
		ll->handle_input = TRUE;
		ll->on_cursor_exit = handle_exit;
		ll->on_cursor_click = handle_click;
		ll->on_cursor_move = handle_resize_ll;

		lr->name = "Lower right corner handle";
		lr->pos = ivec2(w->size.x - DOTS_RADIUS * 2, w->size.y - DOTS_RADIUS * 2);
		lr->size = ivec2(DOTS_RADIUS * 2 * 2, DOTS_RADIUS * 2 * 2);
		ftgr_add_wdrawer(lr, (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)widget_size_handle_drawer});
		lr->handle_input = TRUE;
		lr->on_cursor_exit = handle_exit;
		lr->on_cursor_click = handle_click;
		lr->on_cursor_move = handle_resize_lr;

		move_handle->name = "Move handle";
		move_handle->pos = ivec2(
			w->size.x / 2 + w->pos.x - (MOVE_HANDLE_SIZE / 2),
			w->size.y / 2 + w->pos.y - (MOVE_HANDLE_SIZE / 2));
		move_handle->size = ivec2(MOVE_HANDLE_SIZE, MOVE_HANDLE_SIZE);
		ftgr_add_wdrawer(move_handle, (t_widget_drawer){.draw_f = (t_widget_drawer_draw_f *)widget_move_handle_drawer});

		ftgr_add_widget(ul, rect);
		ftgr_add_widget(ur, rect);
		ftgr_add_widget(ll, rect);
		ftgr_add_widget(lr, rect);
		ftgr_add_widget(move_handle, rect);

		ftgr_add_widget(rect, w);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:17:29 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/04 01:37:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/io.h"
#include <stdlib.h>

#define RADIUS 2

extern t_bitmap_text_infos debug_infos;

// Drawer function for the widget rect ('casing')
static void widget_casing_drawer(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, void *data);
// Darwer function for the size handles (corner dots)
static void widget_size_handle_drawer(t_ftgr_img *out, t_widget *widget, void *data);

// Triggers the on_move callback, if the widget is still clicked, to fix the cursor exiting the widget while dragging
static void handle_exit(t_widget *widget, t_iv2 cursor_pos);

/*
Pour chaque widgets:
1 rect (root), qui englobe le widget + les handles
	- 1er drawer: data: les parametres de l'editeur
	- data: le widget cible

	4 handles:
		- 1er drawer:
			data:
				2 premier bits:
					placement de la handle
						0: upper left
						1: upper right
						2: lower left
						3: lower right
		recuperer les parametres de l'editeur avec handle->master->data
*/

typedef struct s_widget_editor_data
{
	S32 dots_radius;
} t_widget_editor_data;

static void widget_casing_drawer(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, void *data)
{
	t_widget_editor_data *editor_data = (t_widget_editor_data *)data;
	t_iv4 rect = ivec4(abs_pos.x + editor_data->dots_radius, abs_pos.y + editor_data->dots_radius, abs_pos.x + widget->size.x, abs_pos.y + widget->size.y);
	printf("DRAWING RECT: %d %d %d %d\n", rect.x, rect.y, rect.z, rect.w);
	ftgr_draw_rect(out, rect, COL_BLACK);
}

static void widget_size_handle_drawer(t_ftgr_img *out, t_widget *widget, void *data)
{
	t_widget_editor_data *editor_data = (t_widget_editor_data *)widget->master->drawers[0].data;

	t_color col = COL_BLACK;
	if (widget->hovered)
		col = COL_GRAY;
	if (widget->clicked)
		col = COL_RED;

	t_iv2 p = ivec2_add(widget->pos, ivec2_div(widget->size, ivec2(2, 2)));
	ftgr_draw_disc(out, p, editor_data->dots_radius, col);
}

static void handle_move_ul(t_widget *widget, t_iv2 cursor_pos)
{
	t_widget *target = widget->master->data;
	if (widget->clicked)
	{
		t_iv2 delta = ivec2_sub((ivec2_sub(cursor_pos, ivec2(3, 3))), widget->pos);
		target->pos = ivec2_add(target->pos, delta);
	}
}

static void handle_exit(t_widget *widget, t_iv2 cursor_pos)
{
	if (widget->clicked && widget->on_cursor_move)
		widget->on_cursor_move(widget, cursor_pos);
}

static t_widget *init_widget_casing(t_widget_editor_data *data, t_widget *w)
{
	char buff[12];
	string name;
	t_widget *rect = NULL;
	t_widget *ul = NULL, *ur = NULL, *ll = NULL, *lr = NULL;

	if (
		(rect = ftgr_new_widget()) == NULL ||
		(ul = ftgr_new_widget()) == NULL ||
		(ur = ftgr_new_widget()) == NULL ||
		(ll = ftgr_new_widget()) == NULL ||
		(lr = ftgr_new_widget()) == NULL)
	{
		free(rect);
		free(ul);
		free(ur);
		free(ll);
		free(lr);
		return NULL;
	}

	if (w->name)
		name = w->name;
	else
	{
		buff[ft_snprintf(buff, sizeof(buff) - 1, "%p", w)] = '\0';
		name = buff;
	}

	rect->name = ft_strjoin("Casing: ", name);

	rect->pos = ivec2(w->pos.x - data->dots_radius, w->pos.y - data->dots_radius);
	rect->size = ivec2(w->size.x + data->dots_radius, w->size.y + data->dots_radius);
	rect->drawers[rect->drawers_n++] = (t_widget_drawer){.data = data, .cleanup_data = FALSE, .draw_f = (t_widget_drawer_draw_f *)widget_casing_drawer};
	rect->data = w;

	ul = ftgr_new_widget();
	ul->name = "Upper left corner handle";
	ul->pos = ivec2(w->pos.x - data->dots_radius, w->pos.y - data->dots_radius);
	ul->size = ivec2(data->dots_radius * 2, data->dots_radius * 2);
	ul->drawers[ul->drawers_n++] = (t_widget_drawer){.data = NULL, .cleanup_data = FALSE, .draw_f = (t_widget_drawer_draw_f *)widget_size_handle_drawer};
	ul->handle_input = TRUE;
	ul->on_cursor_move = handle_move_ul;
	ul->on_cursor_exit = handle_exit;

	ur = ftgr_new_widget();
	ur->name = "Upper right corner handle";
	ur->pos = ivec2((w->pos.x + w->size.x) - data->dots_radius, w->pos.y - data->dots_radius);
	ur->size = ivec2(data->dots_radius * 2, data->dots_radius * 2);
	ur->drawers[ur->drawers_n++] = (t_widget_drawer){.data = NULL, .cleanup_data = FALSE, .draw_f = (t_widget_drawer_draw_f *)widget_size_handle_drawer};
	ur->handle_input = TRUE;

	ll = ftgr_new_widget();
	ll->name = "Lower left corner handle";
	ll->pos = ivec2(w->pos.x - data->dots_radius, (w->pos.y + w->size.y) - data->dots_radius);
	ll->size = ivec2(data->dots_radius * 2, data->dots_radius * 2);
	ll->drawers[ll->drawers_n++] = (t_widget_drawer){.data = NULL, .cleanup_data = FALSE, .draw_f = (t_widget_drawer_draw_f *)widget_size_handle_drawer};
	ll->handle_input = TRUE;

	lr = ftgr_new_widget();
	lr->name = "Lower right corner handle";
	lr->pos = ivec2((w->pos.x + w->size.x) - data->dots_radius, (w->pos.y + w->size.y) - data->dots_radius);
	lr->size = ivec2(data->dots_radius * 2, data->dots_radius * 2);
	lr->drawers[lr->drawers_n++] = (t_widget_drawer){.data = NULL, .cleanup_data = FALSE, .draw_f = (t_widget_drawer_draw_f *)widget_size_handle_drawer};
	lr->handle_input = TRUE;

	//ftgr_add_widget(ul, rect);
	//ftgr_add_widget(ur, rect);
	//ftgr_add_widget(ll, rect);
	//ftgr_add_widget(lr, rect);

	return rect;
}

// Initializes a new rect, with handles for the specified widget `w`
static void init_widget_editor_rec(t_widget *editor_root, t_widget *w)
{
	t_widget *casing = init_widget_casing(editor_root->data, w);
	ftgr_add_widget(casing, editor_root);
	for (t_widget *w2 = w->childrens; w2; w2 = w2->next)
		init_widget_editor_rec(editor_root, w2);
}

t_widget *init_widget_editor(t_widget *root)
{
	t_widget *editor_root = NULL;
	t_widget_editor_data *editor_data = NULL;

	if ((editor_root = ftgr_new_widget()) == NULL || (editor_data = malloc(sizeof(t_widget_editor_data))) == NULL)
	{
		free(editor_root);
		free(editor_data);
		return NULL;
	}

	editor_data->dots_radius = 3;

	editor_root->name = "Editor";
	editor_root->handle_input = TRUE;
	editor_root->capture_input = FALSE;
	editor_root->data = editor_data;

	if (root)
	{
		for (t_widget *w = root->childrens; w; w = w->next)
			init_widget_editor_rec(editor_root, w);
		ftgr_add_widget(editor_root, root);
	}

	return editor_root;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:07:27 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/18 17:53:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "./3d.h"
#include "libft/lists.h"

struct s_info_line
{
	t_bitmap *bitmap;
	string label_str;
	t_text txt;
	string (*get_value_str)(void *);
	string (*dump_value_str)(void *);
	t_widget *root_w, *dump_btn_w, *infoline_w;
	void *ptr;
};

static void info_line_draw(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, union u_widget_data data)
{
	char buf[1250];

	struct s_info_line *infoline = widget->data.ptr[0];
	string val_str = infoline->get_value_str(infoline->ptr);
	string label = infoline->label_str;

	buf[snprintf(buf, sizeof(buf), "%s: %s", label, val_str)] = '\0';
	infoline->txt.str = buf;
	
	ftgr_draw_bitmap_text(out, ivec4(abs_pos.x, abs_pos.y, widget->size.x + abs_pos.x, widget->size.y + abs_pos.y), infoline->bitmap, infoline->txt, (t_color){
		.r = 222,
		.g = 151,
		.b = 9,
		.a = 255
	});
}

static void info_line_dump(t_widget *widget, t_iv2 cursor_pos)
{
	struct s_info_line *infoline = widget->data.ptr[0];

	string str = infoline->dump_value_str(infoline->ptr);
	printf("--- Dump from widget %s\n%s\n---\n", widget->name, str);
}

t_widget *new_info_line(t_list **lines, t_bitmap *bitmap, string label, string (*get_value_str)(void *), string (*dump_value_str)(void *), void *ptr)
{
	const S32 y_padding = 5;

	S32 infoline_y; /* last infoline y + y_padding */
	S32 txt_height; /* height of a character */
	t_widget *root_w, *dump_btn_w, *infoline_w;
	struct s_info_line *infoline;

	{ /* infoline init */
		infoline = malloc(sizeof(struct s_info_line));
		infoline->bitmap = bitmap;
		infoline->label_str = label;
		infoline->get_value_str = get_value_str;
		infoline->dump_value_str = dump_value_str;
		infoline->ptr = ptr;
		infoline->txt = (t_text){
			.kerning = ivec2(2, 2),
			.scale = 1};
	}

	{ /* Get last infoline Y */
		t_iv2 last_infoline_pos, last_infoline_size;
		t_list *last_infoline;

		last_infoline_pos = ivec2(0, 0);
		last_infoline_size = ivec2(0, 0);

		last_infoline = ft_lstlast(*lines);
		if (last_infoline)
		{
			last_infoline_pos = ((struct s_info_line *)(last_infoline->content))->root_w->pos;
			last_infoline_size = ((struct s_info_line *)(last_infoline->content))->root_w->size;
		}
		infoline_y = last_infoline_pos.y + last_infoline_size.y + y_padding;
	}

	txt_height = ftgr_bitmap_get_height(bitmap, infoline->txt);

	{ /* root init */
		root_w = ftgr_new_widget();
		root_w->name = "Info line root";
		root_w->pos = ivec2(5, infoline_y);
		root_w->size = ivec2(10, txt_height);
	}

	{ /* dump value button init */
		dump_btn_w = ftgr_new_widget();
		dump_btn_w->name = "Dump btn";
		dump_btn_w->pos = ivec2(5, 0);
		dump_btn_w->size = ivec2(10, txt_height);
		if (dump_value_str)
		{
			dump_btn_w->handle_input = TRUE;
			ftgr_wdrawer_paint_rect(dump_btn_w, COL_WHITE);
			dump_btn_w->data = (union u_widget_data){.ptr = {infoline}};
			dump_btn_w->on_cursor_click = (t_widget_callback)info_line_dump;
		}
		else
			ftgr_wdrawer_paint_rect(dump_btn_w, COL_DARK_GRAY);
		ftgr_add_widget(dump_btn_w, root_w);
	}

	{
		infoline_w = ftgr_new_widget();
		infoline_w->name = "Infoline";
		infoline_w->data = (union u_widget_data){.ptr = {infoline}};
		ftgr_add_wdrawer(infoline_w, (t_widget_drawer){.draw_f = info_line_draw});
		infoline_w->pos = ivec2(dump_btn_w->pos.x + dump_btn_w->size.x + infoline->txt.kerning.x, 0);
		infoline_w->size = ivec2(
			1000,
			txt_height);
		ftgr_add_widget(infoline_w, root_w);
	}

	infoline->root_w = root_w;
	infoline->dump_btn_w = dump_btn_w;
	infoline->infoline_w = infoline_w;
	ft_lstadd_back(lines, ft_lstnew(infoline));

	return root_w;
}

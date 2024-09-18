/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:42:25 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/11 22:56:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/limits.h"
#define array_len(a) (sizeof(a) / sizeof(a[0]))

#define STRINGIFY(x) #x
#define XSTRINGIFY(x) STRINGIFY(x)
S16 brush_size = 10;
t_color selected_color = {0, 0, 0, 0};
t_widget *selected_color_widget;
t_ftgr_img *bitmap_img;
t_bitmap text_bitmap;

void select_color(t_widget *w, t_iv2 cursor_pos)
{
	selected_color = w->drawers[0].data.color[0];
	selected_color_widget->drawers[0].data.color[0] = selected_color;
}

int main()
{
	t_label_widget *brush_size_label;

	t_ftgr_ctx *ctx = ftgr_create_ctx();
	t_ftgr_win *win = ftgr_new_window(ctx, ivec2(1024, 768), "paint");

	t_color cols[] = {
		COL_BLACK,
		COL_WHITE,

		COL_RED,
		COL_LIGHT_RED,
		COL_DARK_RED,

		COL_GREEN,
		COL_LIGHT_GREEN,
		COL_DARK_GREEN,

		COL_BLUE,
		COL_LIGHT_BLUE,
		COL_DARK_BLUE,

		COL_GRAY,
		COL_LIGHT_GRAY,
		COL_DARK_GRAY,
	};

#define COLOR_PICKER_RECT_SIZE 30
	win->w_root->handle_input = TRUE;
	for (U64 i = 0; i < array_len(cols); i++)
	{
		t_widget *w = ftgr_new_widget();
		w->pos = ivec2(COLOR_PICKER_RECT_SIZE * i, 0);
		w->size = ivec2(COLOR_PICKER_RECT_SIZE, COLOR_PICKER_RECT_SIZE);
		w->handle_input = TRUE;
		w->name = "Color selector";
		ftgr_wdrawer_paint_rect(w, cols[i]);
		ftgr_wdrawer_draw_rect(w, COL_BLACK);
		w->on_cursor_click = select_color;
		ftgr_add_widget(w, win->w_root);
	}

	selected_color_widget = ftgr_new_widget();
	selected_color_widget->pos = ivec2(array_len(cols) * COLOR_PICKER_RECT_SIZE + 10, 0);
	selected_color_widget->size = ivec2(COLOR_PICKER_RECT_SIZE, COLOR_PICKER_RECT_SIZE);
	selected_color_widget->name = "Selected color";
	ftgr_wdrawer_paint_rect(selected_color_widget, selected_color);
	ftgr_wdrawer_draw_rect(selected_color_widget, COL_BLACK);
	ftgr_add_widget(selected_color_widget, win->w_root);

	{
		bitmap_img = ftgr_load_png(ctx, "../centrale/font_bitmap_black.png");
		if (bitmap_img == NULL)
			goto no_label;
		ftgr_init_bitmap(&text_bitmap, bitmap_img, ivec2(5, 7), 18, ivec2(2, 2));

		brush_size_label = ftgr_label_widget(&text_bitmap);
		brush_size_label->widget.pos = ivec2(2, COLOR_PICKER_RECT_SIZE + 10);
		brush_size_label->widget.name = "Brush size label";
		ftgr_label_update(brush_size_label, "Brush size: 10");
		brush_size_label->widget.size = ivec2(ftgr_bitmap_get_width(&text_bitmap, brush_size_label->infos, NULL), COLOR_PICKER_RECT_SIZE);
		ftgr_wdrawer_paint_rect((t_widget *)brush_size_label, COL_WHITE);
		SWAP(brush_size_label->widget.drawers[0], brush_size_label->widget.drawers[1]);
		ftgr_wdrawer_draw_rect((t_widget *)brush_size_label, COL_BLACK);
		ftgr_add_widget((t_widget *)brush_size_label, win->w_root);
	}
no_label:;

#define BRUSH_SIZE_LABEL_STR_SIZE sizeof("Brush size: ")
	char buffer[BRUSH_SIZE_LABEL_STR_SIZE + U16_MAX_MAG];
	ft_memcpy(buffer, "Brush size: ", BRUSH_SIZE_LABEL_STR_SIZE);

	t_ftgr_img *canvas = ftgr_new_img(ctx, ivec2(win->size.x, win->size.y - COLOR_PICKER_RECT_SIZE - 5));
	t_iv2 last_mouse_pos = ftgr_mouse_get_pos(ctx, win);
	t_iv2 mouse_pos;

	while (ftgr_wait(ctx))
	{
		ftgr_handle_widget_events(win, win->w_root);
		mouse_pos = ftgr_mouse_get_pos(ctx, win);

		{
			if (ftgr_is_key_down(ctx, 'z'))
				brush_size++;
			if (ftgr_is_key_down(ctx, 's'))
				brush_size--;
			brush_size = ft_wrap(brush_size, 1, 100);
			if (ftgr_is_key_down(ctx, 'z') || ftgr_is_key_down(ctx, 's'))
			{
				buffer[ft_itoa_sn(brush_size, buffer + BRUSH_SIZE_LABEL_STR_SIZE - 1, sizeof(buffer) - BRUSH_SIZE_LABEL_STR_SIZE) + BRUSH_SIZE_LABEL_STR_SIZE - 1] = '\0';
				ftgr_label_update(brush_size_label, buffer);
			}
		}

		if (ftgr_mouse_pressed(ctx, MOUSE_LEFT) && mouse_pos.y >= COLOR_PICKER_RECT_SIZE + 5)
		{
			ftgr_draw_disc(canvas, ivec2(mouse_pos.x, mouse_pos.y - COLOR_PICKER_RECT_SIZE - 5), brush_size, selected_color);
		}

		ftgr_cpy_img(win->surface, ivec2(0, COLOR_PICKER_RECT_SIZE + 5), canvas, ivec4(0, 0, canvas->size.x, canvas->size.y));

		ftgr_draw_widget_recursive(win->surface, win->w_root);
		ftgr_swap_buffers(win);

		last_mouse_pos = mouse_pos;
	}
}

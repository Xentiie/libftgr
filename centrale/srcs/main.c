/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 03:12:47 by reclaire          #+#    #+#             */
/*   Updated: 2024/08/04 03:12:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "centrale.h"

#define WIN_SIZE_X 300
#define WIN_SIZE_Y 300

t_color background_col = COL_WHITE;
t_color col = COL_RED;

t_ftgr_ctx *ctx;
t_ftgr_win *main_win;

t_ftgr_img *main_bitmap_img;
t_bitmap main_bitmap;

static void init_bitmap()
{
	main_bitmap_img = ftgr_load_png(ctx, BITMAP_BLACK_PATH);
	main_bitmap = (t_bitmap){.char_height = 7, .char_width = 5, .img = main_bitmap_img, .line_width = 18, .sep_width = 2, .sep_height = 2};
}

void draw_widget_editor_recursive(t_widget *widget, t_ftgr_img *img)
{
	ftgr_draw_rect(img, ivec4(widget->pos.x, widget->pos.y, widget->pos.x + widget->size.x, widget->pos.y + widget->size.y), ftgr_rand_color(0));
	for (t_widget *w = widget->childrens; w; w = w->next)
		draw_widget_editor_recursive(w, img);
}

void draw_all()
{
	ftgr_draw_widget_recursive(main_win->surface, main_win->w_root);
	draw_widget_editor_recursive(main_win->w_root, main_win->surface);
	ftgr_swap_buffers(main_win);
}

int main()
{
	t_widget *text_widget;
	t_bitmap_text_infos text_infos;

	ctx = ftgr_create_ctx();
	init_bitmap();
	main_win = ftgr_new_window(ctx, ivec2(main_bitmap_img->size.x * 4, main_bitmap_img->size.y * 4), "Bitmap");

	{
		// ftgr_wdrawer_stretch_img_cpu(bitmap_widget, main_bitmap_img);
		//ftgr_wdrawer_paint_rect(main_win->w_root, &background_col);
	}

	t_label_widget *label = ftgr_label_widget(&main_bitmap);
	ftgr_label_update(label, "TEST");
	label->widget.pos = ivec2(0, 0);
	label->widget.size = ivec2(100, 100);
	ftgr_add_widget(label, main_win->w_root);

	draw_all();

	while (ftgr_wait(ctx))
	{
		draw_all();

	}
}
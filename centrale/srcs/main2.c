/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 03:12:47 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/06 05:23:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "centrale.h"
#include "libft/io.h"
#include <stdio.h>

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
	main_bitmap_img = ftgr_load_png(BITMAP_BLACK_PATH);
	main_bitmap = (t_bitmap){.char_height = 7, .char_width = 5, .img = main_bitmap_img, .line_width = 18, .sep_width = 2, .sep_height = 2};
}

int main()
{
	ctx = ftgr_create_ctx();
	init_bitmap();
	main_win = ftgr_new_window(ctx, ivec2(main_bitmap_img->size.x * 4, main_bitmap_img->size.y * 4), "Bitmap");
	ftgr_wdrawer_fill_rect(main_win->w_root, COL_WHITE);
	//ftgr_wdrawer_copy_img_cpu(main_win->w_root, main_bitmap_img);

	t_label_widget *label = ftgr_label_widget(&main_bitmap);
	label->widget.name = "Label";
	ftgr_label_update(label, "TEST");
	label->widget.pos = ivec2(10, 10);
	label->widget.size = ivec2(100, 100);
	ftgr_add_widget((t_widget *)label, main_win->w_root);

	t_widget *child = ftgr_new_widget();
	child->pos = ivec2(12, 5);
	child->size = ivec2(30, 30);
	ftgr_wdrawer_fill_rect(child, COL_BLUE);
	//ftgr_add_widget(child, (t_widget *)label);

	while (ftgr_poll(ctx))
	{
		ftgr_draw_widget_recursive(main_win->surface, main_win->w_root);
		ftgr_handle_widget_events(main_win, main_win->w_root);
		ftgr_swap_buffers(main_win);
	}
}

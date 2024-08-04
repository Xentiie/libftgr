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

#include "libftgr.h"

#define WIN_SIZE 300, 300

#define BITMAP_BLACK_PATH "./font_bitmap_black.png"
#define BITMAP_WHITE_PATH "./font_bitmap_white.png"

int main()
{
	t_ftgr_ctx *ctx = ftgr_create_ctx();


	t_widget *terminal = ftgr_new_widget();

	t_ftgr_img *bitmap_black = ftgr_load_png(ctx, BITMAP_BLACK_PATH);
	//t_ftgr_img *bitmap_white = ftgr_load_png(ctx, BITMAP_WHITE_PATH);

	//t_ftgr_win *win = ftgr_new_window(ctx, ivec2(WIN_SIZE), "Centrale");
	t_ftgr_win *win = ftgr_new_window(ctx, bitmap_black->size, "Centrale");

	ftgr_wdrawer_stretch_img_cpu(terminal, bitmap_black);
	ftgr_add_widget(terminal, win->w_root);

	ftgr_draw_widget_recursive(win->surface, win->w_root);
	ftgr_swap_buffers(win);

	while (ftgr_wait(ctx));
}
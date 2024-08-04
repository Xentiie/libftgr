/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:33:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/10 02:33:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./srcs/libftgr_win_int.h"
#include "libftgr.h"
#include "libft/crypt.h"
#include "libft/images.h"
#include "libft/time.h"
#include "libft/io.h"
#include "libft/limits.h"

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>

//https://bobobobo.wordpress.com/2008/02/11/opengl-in-a-proper-windows-app-no-glut/

#define MIN(a, b) (a < b ? a : b)

t_color bg_col = (t_color){ .a = 255, .r = 0, .g = 0, .b = 0 };
t_color bg_col2 = (t_color){ .a = 255, .r = 0, .g = 255, .b = 0 };

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	t_ftgr_ctx *ctx = ftgr_create_ctx();
	t_ftgr_win *win = ftgr_new_window(ctx, ivec2(700, 700), "PNG");
	t_ftgr_img *img1, *img2;

	t_ftgr_img *png = ftgr_load_png(ctx, argv[1]);

	if (png == NULL)
		return 1;

	t_widget *widget_img = ftgr_new_widget();
	widget_img->size = vec2(100, 100);
	widget_img->pos = vec2(0, 100);

	t_color col2 = (t_color){.r = 255, .g = 0, .b = 0, .a = 0};
	ftgr_wdrawer_paint_rect(widget_img, &col2);
	ftgr_add_widget(widget_img, win->w_root);

	float speed = 30.0f;

	t_v2 pos = vec2(0, 0);
	while (ftgr_poll(ctx))
	{
		t_v2 vel = vec2(0, 0);

		//if (ftgr_is_key_pressed(ctx, 'z'))
		//	vel.y -= 1;
		//if (ftgr_is_key_pressed(ctx, 's'))
		//	vel.y += 1;
		//if (ftgr_is_key_pressed(ctx, 'q'))
		//	vel.x -= 1;
		//if (ftgr_is_key_pressed(ctx, 'd'))
		//	vel.x += 1;

		//vel = vec2_scl(vel, ftgr_delta_time(ctx));
		//vel = vec2_scl(vel, speed);
		
		//if (vel.x != 0 || vel.y != 0)
		//	ftgr_move_widget(win, widget_img, vec2_add(widget_img->pos, vel));

		if (ftgr_is_key_down(ctx, 'd'))
		{
			ftgr_draw_widget_recursive(win->surface, win->w_root);
			printf("DRAWING\n");
		}

		if (ftgr_is_key_down(ctx, 's'))
		{
			ftgr_swap_buffers(win);
			col2 = ftgr_rand_color();
			printf("SWAPPED\n");
		}

		if (ftgr_is_key_pressed(ctx, 'z'))
		{
			ftgr_draw_widget_recursive(win->surface, win->w_root);
			ftgr_swap_buffers(win);
			col2 = ftgr_rand_color();
		}

		//ftgr_redraw_rect(win, ivec4(0, 0, win->size.x, win->size.y));

		//ftgr_swap_buffers(win);
		//printf("%p\n", win->surface);
		ftgr_display_fps(win);
	}
	printf("Graceful exit\n");
}
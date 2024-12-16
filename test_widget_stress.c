/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:40:24 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/10 17:45:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

#include "libft/time.h"
#include "libft/io.h"

#include <stdlib.h>
#include <stdio.h>

t_bitmap g_bitmap = (t_bitmap){0};

bool init_bitmap(const_string img_path)
{
	t_ftgr_img *bitmap_img;

	if (g_bitmap.img != NULL)
		return TRUE;

	if ((bitmap_img = ftgr_load_png(img_path)) == NULL)
	{
		ft_fprintf(ft_fstderr, "%s: ftgr_load_png: %s\n", ft_argv[0], ft_strerror2());
		return FALSE;
	}
	for (U64 i = 0; i < bitmap_img->data_size / sizeof(U32); i++)
	{
		if ((((U32 *)bitmap_img->data)[i] & 0x00FFFFFF) == 0)
			((U32 *)bitmap_img->data)[i] = 0x000000FF;
	}
	ftgr_init_bitmap(&g_bitmap, bitmap_img, ivec2(5, 7), 18, ivec2(2, 2));

	return TRUE;
}

void __wdrawer_rect(t_ftgr_img *out, t_widget *widget, t_iv4 rect, union u_widget_data data)
{
	t_iv4 widget_rect;
	t_color col;

	col = data.color[0];
	if (widget->hovered)
	{
		col.r += 30;
		col.g += 30;
		col.b += 30;
	}

	widget_rect = ftgr_widget_rect(widget);
	ftgr_fill_rect_bound2(out, widget_rect, col, rect);
}

void wdrawer_rect(t_widget *widget, U64 *seed)
{
	t_widget_drawer drawer;

	drawer.data.color[0] = ftgr_rand_color(*seed);
	(*seed)++;
	drawer.draw_f = __wdrawer_rect;
	*seed += 1;

	ftgr_add_wdrawer(widget, drawer);
}

void wclick(t_widget *widget, struct s_widget_event_infos infos)
{
	printf("%s: Clicked: %d %d\n", widget->name, infos.cursor_abs_pos.x, infos.cursor_abs_pos.y);
}

void wenter_exit(t_widget *widget, struct s_widget_event_infos infos)
{
	ftgr_widget_damage(infos.win->w_root, ftgr_widget_rect(widget));
}

S32 main()
{
	t_ftgr_ctx *ctx;
	t_ftgr_win *win;

	t_bitmap bitmap;
	t_text txt;

	t_clock clk;
	t_widget **widgets;
	U64 widgets_cnt;
	U64 seed;
	F32 tmp;

	if (ft_argc < 2)
		return 1;

	seed = ft_clk_timestamp();
	ft_clk_init(&clk);
	ctx = ftgr_create_ctx();
	win = ftgr_new_window(ctx, ivec2(400, 400), "widget stress test");
	win->w_root->handle_input = TRUE;
	win->w_root->name = "wroot";
	ftgr_wdrawer_fill_rect(win->w_root, ftgr_color(200, 200, 200, 255));

	init_bitmap("./bitmap.png");

	widgets_cnt = ft_atoi(ft_argv[1]);
	widgets = malloc(sizeof(t_widget *) * widgets_cnt);

	ft_clk_start(&clk);
	for (U64 i = 0; i < widgets_cnt; i++)
	{
		tmp = ft_frand(seed++);
		widgets[i] = ftgr_new_widget();
		widgets[i]->pos = ivec2(
			tmp * win->size.x,
			ft_frand(seed++) * win->size.y);
		widgets[i]->name = ft_saprintf("square_%lu", i);
		widgets[i]->size = ivec2(80, 80);
		widgets[i]->handle_input = TRUE;
		widgets[i]->capture_input = TRUE;
		widgets[i]->on_cursor_click = wclick;
		widgets[i]->on_cursor_enter = wenter_exit;
		widgets[i]->on_cursor_exit = wenter_exit;
		wdrawer_rect(widgets[i], &seed);
		txt.kerning = ivec2(2, 2);
		txt.scale = 2.0f;
		txt.str = widgets[i]->name;
		ftgr_wdrawer_draw_text(widgets[i], &bitmap, &txt, COL_WHITE);
		ftgr_add_widget(widgets[i], win->w_root);
	}
	ft_clk_stop(&clk);

	ftgr_widget_damage(win->w_root, ftgr_widget_rect(win->w_root));
	bool mode = FALSE;
	while (ftgr_wait(ctx))
	{
		ftgr_handle_widget_events(win, win->w_root);
		if (ftgr_mouse_down(ctx, MOUSE_LEFT))
		{
			mode = !mode;
			if (mode)
				printf("ftgr_draw_widget_recursive\n");
			else
				printf("ftgr_draw_widget_damage\n");
		}

		if (mode)
		{
			ftgr_draw_widget_recursive(win->surface, win->w_root);
			ftgr_swap_buffers(win);
		}
		else
		{
			if (ftgr_draw_widget_damage(win->surface, win->w_root))
				ftgr_blt_screen(win);
		}

		ftgr_display_fps(win);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:48:14 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/11 03:38:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libftgr.h"
#include "libft/io.h"

void draw_bezier(t_ftgr_ctx *ctx, t_ftgr_win *win, t_ftgr_img *img)
{
	static int increments = 3;

	static t_v2 points[3] = {{10, 200}, {100, 150}, {200, 250}};
	static S32 selectionned = -1;
	static bool dirty = TRUE;

	if (ftgr_is_key_down(ctx, 'z'))
	{
		increments++;
		printf("%d\n", increments);
		dirty = TRUE;
	}
	if (ftgr_is_key_down(ctx, 's'))
	{
		increments--;
		dirty = TRUE;
	}

	if (ftgr_mouse_click(ctx, MOUSE_LEFT))
	{
		for (int i = 0; i < 3; i++)
		{
			t_iv2 mouse_pos = ftgr_mouse_get_pos(ctx, win);
			if (ft_dist2(ivec2_flt(mouse_pos), points[i]) <= 10)
			{
				selectionned = i;
				break;
			}
		}
	}
	if (ftgr_mouse_pressed(ctx, MOUSE_LEFT) && selectionned != -1)
	{
		dirty = TRUE;
		points[selectionned] = ivec2_flt(ftgr_mouse_get_pos(ctx, win));
		points[selectionned].x = ft_clamp(10, img->size.x, points[selectionned].x - 10);
		points[selectionned].y = ft_clamp(10, img->size.y, points[selectionned].y - 10);
	}
	else
		selectionned = -1;

	if (dirty)
	{
		ft_memset(img->data, 0, img->data_size * (img->pixel_size / 8));
		ftgr_draw_bezier(img, COL_WHITE, points[0], points[1], points[2], increments);
		ftgr_draw_disc(img, vec2_int(points[0]), 10, COL_GRAY);
		ftgr_draw_disc(img, vec2_int(points[1]), 10, COL_GRAY);
		ftgr_draw_disc(img, vec2_int(points[2]), 10, COL_GRAY);
		ftgr_display_image(img, win, ivec2(0, 0));
		dirty = FALSE;
	}
}

int main()
{
	const S32 sizex = 500;
	const S32 sizey = 300;

	t_ftgr_ctx *ctx = ftgr_create_ctx();
	t_ftgr_win *win = ftgr_new_window(ctx, ivec2(sizex, sizey), "Text");
	ftgr_move_window(win, ivec2(sizex, sizey));

	t_ftgr_img *img = ftgr_new_img(ctx, ivec2(sizex, sizey));

	file fd = ft_fopen("./font2.ttf", "r");
	ftgr_load_font(fd, img);
	ft_fclose(fd);
	ftgr_display_image(img, win, ivec2(0, 0));

	while (ftgr_poll(ctx))
	{
		ftgr_display_fps(win);
		//draw_bezier(ctx, win, img);
	}
}
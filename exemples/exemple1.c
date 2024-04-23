/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:49:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/04/23 04:22:12 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include <stdio.h>
#include "libft/lists.h"
#include <stdlib.h>

float up = 0.0f;
float right = 0.0f;

void draw_sin(t_ftgr_ctx *ctx, t_ftgr_img *img)
{
	for (int x = 0; x < img->size.x; x++)
	{
		float f1 = (sinf((float)x/img->size.x * 50 + right*10) + 1) / 2.0f;
		for (int y = 0; y < img->size.y; y++)
		{
			float f2 = (sinf((float)y/img->size.y * 50 + up*10) + 1) / 2.0f;
			float f = f1 * f2;
			ftgr_set_pixel(img, ivec2(x, y), (t_color){.r = f*255, .g = f*255, .b = f*255, .a=0});
		}
	}
}

bool cmp(int *a, int *b)
{ return *a == *b; }

int main()
{

	t_ftgr_ctx *ctx = ftgr_create_ctx();
	t_ftgr_win *win = ftgr_new_window(ctx, ivec2(300, 300), "test");

	t_ftgr_img *img = ftgr_new_img(ctx, ivec2(300, 300));
	ftgr_key_autorepeat(ctx, FALSE);

	while (ftgr_poll(ctx))
	{
		ftgr_display_fps(win);
		draw_sin(ctx, img);

		float dtime = ftgr_delta_time(ctx);
		if (ftgr_is_key_down(ctx, 'z'))
		{ printf("Going up !!\n"); }
		if (ftgr_is_key_down(ctx, 's'))
		{ printf("Going down !!\n"); }
		if (ftgr_is_key_down(ctx, 'q'))
		{ printf("Going left !!\n"); }
		if (ftgr_is_key_down(ctx, 'd'))
		{ printf("Going right !!\n"); }

		if (ftgr_is_key_pressed(ctx, 'z'))
			up += dtime;
		if (ftgr_is_key_pressed(ctx, 's'))
			up -= dtime;
		if (ftgr_is_key_pressed(ctx, 'q'))
			right += dtime;
		if (ftgr_is_key_pressed(ctx, 'd'))
			right -= dtime;

		ftgr_display_image(img, win, ivec2(0, 0));
	}
	ftgr_key_autorepeat(ctx, TRUE);
	printf("Adios !\n");
	ftgr_free_img(img);
	ftgr_free(ctx);
}

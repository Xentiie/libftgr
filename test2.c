/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:33:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/03 16:23:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/crypt.h"
#include "libft/images.h"
#include "libft/time.h"
#include "libft/io.h"

#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (a < b ? a : b)


int main(int argc, char **argv)
{
	/*
	struct {
		U64 a;
		U64 b;
	} t;
	t.a = 0x807060504030201;
	t.b = 0x100f0e0d0c0b0a09;
	for (int i = 0; i < 16; i++)
		printf("%#x\n", ((U8*)&t)[i]);
	return 0;
	*/

	if (argc != 2)
		return 1;

	t_ftgr_ctx *ctx = ftgr_create_ctx();
	t_ftgr_win *win = ftgr_new_window(ctx, ivec2(800, 800), "PNG");
	t_ftgr_img *display_img = ftgr_new_img(ctx, ivec2(800, 800));
	t_ftgr_img *png = ftgr_load_png(ctx, argv[1]);

	if (png == NULL)
		return 1;

	for (U64 y = 0; y < display_img->size.y; y++)
	{
		for (U64 x = 0; x < display_img->size.x; x++)
		{
			t_v2 t = ft_invlerp2(vec2(0, 0), ivec2_flt(display_img->size), vec2(x, y));
			S64 x2 = ft_lerp(0, png->size.x, t.x);
			S64 y2 = ft_lerp(0, png->size.y, t.y);

			S64 ind = (S64)((y2 * png->size.x + x2));

			U32 *addr1 = (U32*)(png->data + (x2 + y2 * png->size.x) * 4);
			U32 *addr2 = (U32*)(display_img->data + (x + y * display_img->size.x) * 4);
			*addr2 = *addr1;
		}
	}

	ftgr_display_image(png, win, ivec2(0, 0));

	t_iv2 prev_pos = ivec2(-1, -1);
	t_iv2 img_pos = ivec2(0, 0);
	while (ftgr_poll(ctx))
	{
		if (ftgr_mouse_down(ctx, MOUSE_LEFT))
			prev_pos = ftgr_mouse_get_pos(ctx, win);
		if (ftgr_mouse_released(ctx, MOUSE_LEFT))
			prev_pos = ivec2(-1, -1);

		if (prev_pos.x != -1)
		{
			img_pos = ivec2_add(img_pos, ivec2_sub(ftgr_mouse_get_pos(ctx, win), prev_pos));
			prev_pos = ftgr_mouse_get_pos(ctx, win);
			ftgr_display_image(png, win, img_pos);
		}

		ftgr_display_fps(win);
	}
}
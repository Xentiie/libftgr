/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stretch_img_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:26:05 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/14 18:30:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

#include "libft/io.h"
#include "libft/time.h"

void stretch_bounded_noablend(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect);

void stretch_img_test()
{
	t_ftgr_ctx *ctx;
	t_ftgr_win *win;

	t_iv4 srcrect;
	t_iv4 dstrect;
	t_iv4 osrcrect;
	t_iv4 odstrect;
	bool haveo = FALSE;
	bool src_c1 = FALSE;
	bool src_c2 = FALSE;
	bool dst_c1 = FALSE;
	bool dst_c2 = FALSE;

	t_iv2 winsize = ivec2(1080, 720);
	t_iv4 test_img_rect = ivec4(0, 0, 200, 200);
	t_iv4 test_rect = ivec4(test_img_rect.x + test_img_rect.z, 0, winsize.x - (test_img_rect.x + test_img_rect.z), winsize.y);

	ctx = ftgr_new_ctx();
	win = ftgr_new_window(ctx, winsize, "Test");

	t_image *img = ftgr_new_img(ivec2(test_img_rect.z, test_img_rect.w));
	for (S32 x = 0; x < img->size.x; x++)
	{
		for (S32 y = 0; y < img->size.y; y++)
			*ftgr_get_pixel(img, x, y) = ftgr_color(x / (F32)img->size.x * 255, y / (F32)img->size.y * 255, 0, 255);
	}

	t_iv2 mousepos;
	while (ftgr_wait(ctx))
	{
		mousepos = ftgr_mouse_get_pos(ctx, win);

		ftgr_fill_rect(win->surface, ivec4(0, 0, winsize.x, winsize.y), ftgr_color(0, 0, 0, 255));
		ftgr_cpy_img(win->surface, ivec2(test_img_rect.x, test_img_rect.y), img, ivec4(0, 0, img->size.x, img->size.y));
		if (haveo)
			stretch_bounded_noablend(win->surface, odstrect, img, osrcrect);

		ftgr_draw_rect(win->surface, ivec4_sub(test_img_rect, ivec4(0, 0, 1, 1)), ftgr_color(255, 255, 255, 255));
		ftgr_draw_rect(win->surface, ivec4_sub(test_rect, ivec4(0, 0, 1, 1)), ftgr_color(255, 255, 255, 255));

		if (src_c1)
		{
			if (src_c2)
				ftgr_draw_rect2(win->surface, srcrect, ftgr_color(255, 255, 255, 255));
			else
				ftgr_draw_rect2(win->surface, ivec4(srcrect.x, srcrect.y, mousepos.x, mousepos.y), ftgr_color(255, 255, 255, 127));
		}

		if (dst_c1)
		{
			if (dst_c2)
				ftgr_draw_rect2(win->surface, dstrect, ftgr_color(255, 255, 255, 255));
			else
				ftgr_draw_rect2(win->surface, ivec4(dstrect.x, dstrect.y, mousepos.x, mousepos.y), ftgr_color(255, 255, 255, 127));
		}

		if (ftgr_mouse_down(ctx, MOUSE_LEFT))
		{
			if (!src_c1)
			{
				if (mousepos.x < test_img_rect.x || mousepos.x >= test_img_rect.z ||
					mousepos.y < test_img_rect.y || mousepos.y >= test_img_rect.w)
					continue;
				srcrect.x = mousepos.x;
				srcrect.y = mousepos.y;

				src_c1 = TRUE;
			}
			else if (!src_c2)
			{
				if (mousepos.x < test_img_rect.x || mousepos.x >= test_img_rect.z ||
					mousepos.y < test_img_rect.y || mousepos.y >= test_img_rect.w)
					continue;
				srcrect.z = mousepos.x;
				srcrect.w = mousepos.y;

				src_c2 = TRUE;
			}
			if (!dst_c1)
			{
				if (mousepos.x < test_rect.x || mousepos.x >= test_rect.z ||
					mousepos.y < test_rect.y || mousepos.y >= test_rect.w)
					continue;
				dstrect.x = mousepos.x;
				dstrect.y = mousepos.y;

				dst_c1 = TRUE;
			}
			else if (!dst_c2)
			{
				if (mousepos.x < test_rect.x || mousepos.x >= test_rect.z ||
					mousepos.y < test_rect.y || mousepos.y >= test_rect.w)
					continue;
				dstrect.z = mousepos.x;
				dstrect.w = mousepos.y;

				dst_c2 = TRUE;
			}

			if (src_c1 && src_c2 && dst_c1 && dst_c2)
			{
				stretch_bounded_noablend(win->surface, dstrect, img, srcrect);
				osrcrect = srcrect;
				odstrect = dstrect;
				haveo = TRUE;
				src_c1 = FALSE;
				src_c2 = FALSE;
				dst_c1 = FALSE;
				dst_c2 = FALSE;
			}
		}

		DBGUI_begin(mousepos);
		DBGUI_text("src_c1:%d src_c2:%d srcrect: %d %d %d %d", src_c1, src_c2, srcrect.x, srcrect.y, srcrect.z, srcrect.w);
		DBGUI_text("dst_c1:%d dst_c2:%d dstrect: %d %d %d %d", dst_c1, dst_c2, dstrect.x, dstrect.y, dstrect.z, dstrect.w);
		DBGUI_render(win->surface);

		ftgr_blt_screen(win);
	}
}

void stretch_img_benchmark()
{
	t_iv2 image1_size;
	t_iv2 image2_size;
	t_image image1;
	t_image image2;
	t_clock clk;

	ft_clk_init(&clk);

	image1_size = ivec2(8192 * 2, 8192 * 2);
	image2_size = ivec2(8192 * 2, 8192 * 2);

	ft_init_image(&image1, image1_size);
	ft_init_image(&image2, image2_size);

	ft_clk_start(&clk);
	stretch_bounded_noablend(&image1, ivec4(0, 0, image1_size.x, image1_size.y), &image2, ivec4(0, 0, image2_size.x, image2_size.y));
	ft_clk_stop(&clk);
	ft_printf("Took: %s\n", ft_clk_fmt_elapsed_str(&clk));

	ft_destroy_image(&image1);
	ft_destroy_image(&image2);
}

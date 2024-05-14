/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:33:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/14 01:41:05 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
//#include "libftgr_ui.h"
#include <stdio.h>

int main()
{
	t_ftgr_ctx *ctx = ftgr_create_ctx();
	t_ftgr_win *win = ftgr_new_window(ctx, ivec2(400, 400), "Test");

	t_ftgr_img *img = ftgr_new_img(ctx, ivec2(400, 400));
	ft_memset(img->data, 0x5F, img->data_size);

	t_ftgr_img *img2 = ftgr_new_img(ctx, ivec2(400, 400));
	for (int x = 0; x < 400; x++)
		for (int y = 0; y < 400; y++)
		{
			ftgr_set_pixel(img, ivec2(x, y), (t_color){0, 0, 255, 127});
			ftgr_set_pixel(img2, ivec2(x, y), (t_color){255, 0, 0, 127});
		}

	ftgr_display_image(img, win, ivec2(0, 0));
	ftgr_display_image(img2, win, ivec2(0, 0));

	while (ftgr_poll(ctx))
	{
	}

	ftgr_free(ctx);
}

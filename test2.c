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

#define MIN(a, b) (a < b ? a : b)

void stretch(t_ftgr_img *dst, t_iv4 dst_rect, t_ftgr_img *src, t_iv4 src_rect)
{
	S32 dst_w = dst_rect.z - dst_rect.x;
	S32 dst_h = dst_rect.w - dst_rect.y;

	S32 src_w = src_rect.z - src_rect.x;
	S32 src_h = src_rect.w - src_rect.y;

	S32 *x_vals = alloca(sizeof(S32) * dst_w);
	for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		x_vals[x - dst_rect.x] = (S32)(src_rect.x + ((x - dst_rect.x) / (F32)dst_w) * src_w);

	for (S32 y = dst_rect.y; y < dst_rect.w; y++)
	{
		for (S32 x = dst_rect.x; x < dst_rect.z; x++)
		{
			U32 dst_addr = ((x + y * dst->size.x) * dst->bpp);
			U32 src_addr = ((
								x_vals[x - dst_rect.x] +
								((S32)(src_rect.y + ((y - dst_rect.y) / (F32)dst_h) * src_h) * src->size.x)) *
							src->bpp);
			*(U32 *)(dst->data + dst_addr) = *(U32 *)(src->data + src_addr);
		}
	}
}

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

	ctx->widget_root->pos = vec2(0, 0);
	ctx->widget_root->size = vec2(700, 700);
	ftgr_wdrawer_stretch_img_cpu(ctx->widget_root, png);

	t_widget *widget_img = ftgr_new_widget();
	widget_img->size = vec2(100, 100);
	ftgr_wdrawer_stretch_img_cpu(widget_img, png);
	ftgr_add_widget(widget_img, ctx->widget_root);

	float speed = 30.0f;

	while (ftgr_poll(ctx))
	{
		t_v2 vel = vec2(0, 0);

		if (ftgr_is_key_pressed(ctx, 'z'))
			vel.y -= 1;
		if (ftgr_is_key_pressed(ctx, 's'))
			vel.y += 1;
		if (ftgr_is_key_pressed(ctx, 'q'))
			vel.x -= 1;
		if (ftgr_is_key_pressed(ctx, 'd'))
			vel.x += 1;

		vel = vec2_scl(vel, ftgr_delta_time(ctx));
		vel = vec2_scl(vel, speed);
		ftgr_move_widget(win, widget_img, vec2_add(widget_img->pos, vel));

		ftgr_display_fps(win);
	}
	printf("Graceful exit\n");
}
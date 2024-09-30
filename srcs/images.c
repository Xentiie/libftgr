/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 03:03:13 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/21 01:08:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include <stdlib.h>

t_ftgr_img *ftgr_new_img(t_ftgr_ctx *ctx, t_iv2 size)
{
	(void)ctx;
	t_ftgr_img *img = malloc(sizeof(t_ftgr_img));
	if (!img)
		return NULL;

	img->size = size;
	img->bpp = 4;
	img->line_size = img->bpp * size.x;
	img->data_size = img->line_size * size.y;
	img->data = malloc(sizeof(U8) * img->data_size);
	if (!img->data)
	{
		free(img);
		return NULL;
	}

	return img;
}

void ftgr_display_image(t_ftgr_img *img, t_ftgr_win *win, t_iv2 pos)
{
	ftgr_cpy_img(win->surface, pos, img, ivec4(0, 0, img->size.x, img->size.y));
}

void ftgr_free_img(t_ftgr_img *img)
{
	free(img->data);
	free(img);
}

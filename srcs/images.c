/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 03:03:13 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/14 03:07:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _FT_RETURN

#include "libftgr.h"

#include <stdlib.h>

t_image *ftgr_new_img(t_iv2 size)
{
	t_image *img;
	
	if (UNLIKELY((img = malloc(sizeof(t_image))) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);

	if (!ftgr_init_img(img, size))
	{
		free(img);
		FT_RET_ERR(NULL, ft_errno);
	}

	FT_RET_OK(img);
}

bool ftgr_init_img(t_image *img, t_iv2 size)
{
	if (UNLIKELY((img->data = malloc(sizeof(t_color) * size.x * size.y)) == NULL))
		FT_RET_ERR(FALSE, FT_EOMEM);

	img->size = size;
	img->pixels = (t_color *)img->data;

	FT_RET_OK(TRUE);
}

void ftgr_display_image(t_image *img, t_ftgr_win *win, t_iv2 pos)
{
	ftgr_cpy_img(win->surface, pos, img, ivec4(0, 0, img->size.x, img->size.y));
}

void ftgr_free_img(t_image *img)
{
	free(img->data);
	free(img);
}

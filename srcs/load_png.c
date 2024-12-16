/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:43:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/10 05:30:01 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/images.h"
#include "libft/io.h"

t_ftgr_img *ftgr_load_png(const_string path)
{
	filedesc fd = ft_open((string)path, "r");
	t_png_img *png = ft_load_png(fd, TRUE);
	ft_close(fd);

	if (UNLIKELY(png == NULL) || (png->color_type != 0 && png->color_type != 2 && png->color_type != 4 && png->color_type != 6))
		return FALSE;

	t_ftgr_img *img = ftgr_new_img(ivec2(png->width, png->height));
	if (UNLIKELY(img == NULL))
	{
		ft_free_png_img(png);
		return FALSE;
	}

	switch (png->color_type)
	{
	case 0:
		for (U64 i = 0; i < (png->width * png->height); i++)
			img->pixels[i] = ftgr_color(png->data[i], png->data[i], png->data[i], 255);
		break;
	case 2:
		for (U64 i = 0; i < (png->width * png->height); i++)
			img->pixels[i] = ftgr_color(png->data[i * 3], png->data[i * 3 + 1], png->data[i * 3 + 2], 255);
		break;
	case 4:
		for (U64 i = 0; i < (png->width * png->height); i++)
			img->pixels[i] = ftgr_color(png->data[i * 2], png->data[i * 2 + 1], png->data[i * 2 + 2], 255);
		break;
	case 6:
		for (U64 i = 0; i < (png->width * png->height); i++)
			img->pixels[i] = *(t_color *)(png->data + i * 4);
		break;
	}

	ft_free_png_img(png);
	return img;
}

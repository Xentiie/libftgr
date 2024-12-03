/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:43:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/03 19:25:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/images.h"
#include "libft/io.h"

t_ftgr_img	*ftgr_load_png(t_ftgr_ctx *ctx, const_string path)
{
	filedesc fd = ft_open((string)path, "r");
	t_png_img *png = ft_load_png(fd, TRUE);
	ft_close(fd);

	if (UNLIKELY(png == NULL) || (png->color_type != 0 && png->color_type != 2 && png->color_type != 4 && png->color_type != 6) )
		return FALSE;

	t_ftgr_img *img = ftgr_new_img(ctx, ivec2(png->width, png->height));
	if (UNLIKELY(img == NULL))
	{
		ft_free_png_img(png);
		return FALSE;
	}

	t_color c;
	switch (png->color_type)
	{
	case 0:
		for (U64 i = 0; i < (png->width * png->height); i++)
		{
			c = (t_color){ .r=png->data[i], .g=png->data[i], .b=png->data[i], .a=255 };
			((U32*)img->data)[i] = ftgr_color_to_int(c);
		}
		break;
	case 2:
		for (U64 i = 0; i < (png->width * png->height); i++)
		{
			c = (t_color){ .r=png->data[i * 3], .g=png->data[i * 3 + 1], .b=png->data[i * 3 + 2], .a=255 };
			((U32*)img->data)[i] = ftgr_color_to_int(c);
		}
		break;
	case 4:
		for (U64 i = 0; i < (png->width * png->height); i++)
		{
			c = (t_color){ .r=png->data[i * 2], .g=png->data[i * 2 + 1], .b=png->data[i * 2 + 2], .a=255 };
			((U32*)img->data)[i] = ftgr_color_to_int(c);
		}
		break;
	case 6:
		for (U64 i = 0; i < (png->width * png->height); i++)
		{
			c = *(t_color*)(png->data + i * 4);
			((U32*)img->data)[i] = ftgr_color_to_int(c);
		}
		break;
	}

	ft_free_png_img(png);
	return img;
}

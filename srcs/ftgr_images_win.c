/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_images_win.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:51:47 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/04 16:09:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int_win.h"
#include "libft/time.h"

t_ftgr_img *ftgr_new_img(t_ftgr_ctx *ctx, t_iv2 size)
{
	t_ftgr_img *img = malloc(sizeof(t_ftgr_img) + sizeof(t_ftgr_img_int));
	if (!img)
		return NULL;
	t_ftgr_img_int *img_int = (t_ftgr_img_int *)(((char *)img) + sizeof(t_ftgr_img));
	img->internal = img_int;

	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = size.x;
	bmi.bmiHeader.biHeight = -size.y; // Negative height to indicate top-down bitmap
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; // Assuming 32-bit RGBA pixel format
	bmi.bmiHeader.biCompression = BI_RGB;

	img_int->bitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&img->data, NULL, 0);
	CHECKRET(img_int->bitmap);

	img->ctx = ctx;
	img->size = size;
	img->pixel_size = 32;
	img->line_size = 32 / 8 * size.x;
	img->data_size = img->line_size * size.y;

	return img;
}

void ftgr_display_image(t_ftgr_img *img, t_ftgr_win *win, t_iv2 pos)
{
	t_ftgr_img_int *img_int = FTGR_IMAGE_INT(img);

	HDC memDC = CreateCompatibleDC(NULL);
	CHECKRET(memDC);

	HBITMAP oldBitmap = SelectObject(memDC, img_int->bitmap);
	CHECKRET(oldBitmap);

	CHECKRET(BitBlt(win->dc, 0, 0, img->size.x, img->size.y, memDC, 0, 0, SRCCOPY));

	CHECKRET(SelectObject(memDC, oldBitmap));
	CHECKRET(DeleteDC(memDC));
}

void ftgr_set_pixel(t_ftgr_img *img, t_iv2 p, t_color col)
{
	U8 *addr = &(((U64 *)img->data)[(p.x + p.y * img->size.x) * img->pixel_size/8]);
	addr[0] = col.b;
	addr[1] = col.g;
	addr[2] = col.r;
	addr[3] = col.a;
}

t_color ftgr_rand_color()
{
	t_time t;
	clk_get(&t);

	return (t_color){.r = ft_frand(t.nanoseconds), .g = ft_frand(t.nanoseconds + 1), .b = ft_frand(t.nanoseconds + 2), .a = 255};
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:51:47 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/10 04:26:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_win_int.h"
#include "libft/time.h"

#ifdef FT_OS_WIN

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
#if CACHE_IMAGE_DC == 1
	img_int->dc = CreateCompatibleDC(NULL);
	CHECKRET(img_int->dc);
	CHECKRET(SelectObject(img_int->dc, img_int->bitmap));
#endif

	img->ctx = ctx;
	img->size = size;
	img->pixel_size = 32;
	img->bpp = img->pixel_size / 8;
	img->line_size = img->bpp * size.x;
	img->data_size = img->line_size * size.y;

	return img;
}

void ftgr_display_image(t_ftgr_img *img, t_ftgr_win *win, t_iv2 pos)
{
#if CACHE_IMAGE_DC == 1
		t_ftgr_img_int *img_int = FTGR_IMAGE_INT(img);
		CHECKRET(BitBlt(win->dc, pos.x, pos.y, img->size.x, img->size.y, img_int->dc, 0, 0, SRCCOPY));
#else
		HDC memDC = CreateCompatibleDC(NULL);
		CHECKRET(memDC);
		HBITMAP oldBitmap = SelectObject(memDC, FTGR_IMAGE_INT(img)->bitmap);
		CHECKRET(oldBitmap);
		//CHECKRET(BitBlt(win->dc, pos.x, pos.y, img->size.x, img->size.y, memDC, 0, 0, SRCCOPY));
		CHECKRET(StretchBlt(win->dc, 0, 0, win->size.x, win->size.y, memDC, 0, 0, img->size.x, img->size.y, SRCCOPY));
		CHECKRET(SelectObject(memDC, oldBitmap));
		CHECKRET(DeleteDC(memDC));
#endif
}

void ftgr_free_img(t_ftgr_img *img)
{
	//CHECKRET(DeleteDC(FTGR_IMAGE_INT(img)->dc));
}

/*
void ftgr_set_pixel(t_ftgr_img *img, t_iv2 p, t_color col)
{
	U8 *addr = &(((U64 *)img->data)[(p.x + p.y * img->size.x) * img->pixel_size/8]);
	addr[0] = col.b;
	addr[1] = col.g;
	addr[2] = col.r;
	addr[3] = col.a;
}
*/

#endif
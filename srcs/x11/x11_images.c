/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:02:37 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/04 16:16:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_x11_int.h"

t_ftgr_img *ftgr_new_img(t_ftgr_ctx *ctx, t_iv2 size)
{
	t_ftgr_img *img = malloc(sizeof(t_ftgr_img) + sizeof(t_ftgr_img_int));
	if (!img)
		return NULL;
	t_ftgr_img_int *img_int = (t_ftgr_img_int *)(((char *)img) + sizeof(t_ftgr_img));
	img->internal = img_int;

	if (!(img->data = malloc((size.x + 32) * size.y * 4)))
	{
		free(img);
		return NULL;
	}
	ft_memset(img->data, 0, (size.x + 32) * size.y * 4);

	img_int->img = XCreateImage(ctx->display, ctx->visual, ctx->depth, ZPixmap, 0,
								img->data, size.x, size.y, 32, 0);
	if (!img_int->img)
	{
		free(img->data);
		free(img);
		return ((void *)0);
	}

	img_int->pixmap = XCreatePixmap(ctx->display, ctx->root, size.x, size.y, ctx->depth);
	img_int->format = ZPixmap;
	img_int->shm = FALSE;
	img_int->gc = 0;

	img->line_size = img_int->img->bytes_per_line;
	img->pixel_size = img_int->img->bits_per_pixel;
	img->size = size;
	img->ctx = ctx;
	img->data_size = img->size.x * img->size.y * img->pixel_size/8;
	if (ctx->flush)
		XFlush(ctx->display);
	return (img);
}

U8 *ftgr_get_img_data(t_ftgr_img *img)
{
	
}

void ftgr_display_image(t_ftgr_img *img, t_ftgr_win *win, t_iv2 pos)
{
	t_ftgr_img_int *img_int = FTGR_IMAGE_INT(img);

	GC gc = win->gc;
	if (img_int->gc)
	{
		gc = img_int->gc;
		XSetClipOrigin(img->ctx->display, gc, pos.x, pos.y);
	}

	if (img_int->shm)
	{
	}
	else
	{
		XPutImage(win->ctx->display, img_int->pixmap, win->gc, img_int->img, 0, 0, 0, 0,
				  img->size.x, img->size.y);
	}

	XCopyArea(win->ctx->display, img_int->pixmap, win->window, gc,
			  0, 0, img->size.x, img->size.y, pos.x, pos.y);
	if (win->ctx->flush)
		XFlush(win->ctx->display);
}

void ftgr_set_pixel(t_ftgr_img *img, t_iv2 p, t_color col)
{
	U32 c = ftgr_color_to_int(col);
	*(U32 *)(img->data + (p.y * img->line_size + p.x * (img->pixel_size / 8))) = c;
}

void ftgr_free_img(t_ftgr_img *img)
{
	t_ftgr_img_int *img_int = FTGR_IMAGE_INT(img);

	if (img_int->gc)
		XFreeGC(img->ctx->display, img_int->gc);
	XFreePixmap(img->ctx->display, img_int->pixmap);
	XDestroyImage(img_int->img);
	// free(img->data);
	free(img);
}

t_color ftgr_rand_color()
{
	t_time t;
	clk_get(&t);

	return (t_color){.r = ft_frand(t.nanoseconds)*255, .g = ft_frand(t.nanoseconds + 1)*255, .b = ft_frand(t.nanoseconds + 2)*255, .a = 255};
}

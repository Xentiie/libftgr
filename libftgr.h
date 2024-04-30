/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:46 by reclaire          #+#    #+#             */
/*   Updated: 2024/04/28 22:01:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTGR_H
#define LIBFTGR_H

#include "libft/std.h"
#include "libft/strings.h"
#include "libft/maths.h"
#include "srcs/libftgr_constants.h"

typedef void *t_ftgr_ctx;
typedef void *t_ftgr_win;
typedef void *t_opencl_ctx;

typedef struct
{
	U64 line_size;
	U64 pixel_size;
	char *data;
	t_iv2 size;

	t_ftgr_ctx *ctx;
	void *internal;
} t_ftgr_img;

typedef struct {
	U8 r;
	U8 g;
	U8 b;
	U8 a;
}	t_color;


t_ftgr_ctx *ftgr_create_ctx();
bool ftgr_wait(t_ftgr_ctx *ctx);
bool ftgr_poll(t_ftgr_ctx *ctx);

t_ftgr_win *ftgr_new_window(t_ftgr_ctx *ctx, t_iv2 size, const_string title);
void ftgr_free_window(t_ftgr_ctx *win);
void ftgr_set_win_name(t_ftgr_win *win, string name);
void ftgr_set_win_name_infos(t_ftgr_win *win, string infos);

void ftgr_free(t_ftgr_ctx *ctx);

void ftgr_bring_top(t_ftgr_win *win);

void ftgr_mouse_move(t_ftgr_ctx *ctx, t_ftgr_win *win, t_iv2 pos);
void ftgr_mouse_hide(t_ftgr_ctx *ctx, t_ftgr_win *win);
void ftgr_mouse_show(t_ftgr_ctx *ctx, t_ftgr_win *win);
t_iv2 ftgr_mouse_get_pos(t_ftgr_ctx *ctx, t_ftgr_win *win);

bool ftgr_is_key_pressed(t_ftgr_ctx *ctx, U32 key);
bool ftgr_is_key_down(t_ftgr_ctx *ctx, U32 key);
bool ftgr_is_key_up(t_ftgr_ctx *ctx, U32 key);
void ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active);

void ftgr_set_error_callback(t_ftgr_ctx *ctx, void (*callback)());

float ftgr_time(t_ftgr_ctx *ctx);
float ftgr_delta_time(t_ftgr_ctx *ctx);

t_ftgr_img *ftgr_new_img(t_ftgr_ctx *ctx, t_iv2 size);
void ftgr_free_img(t_ftgr_img *img);
void ftgr_display_image(t_ftgr_img *img, t_ftgr_win *win, t_iv2 pos);
void ftgr_set_pixel(t_ftgr_img *img, t_iv2 p, t_color col);

void ftgr_display_fps(t_ftgr_win *win);
S32 ftgr_color_to_int(t_color col);

t_opencl_ctx *ftgr_create_opencl_ctx();
void ftgr_opencl_render(t_opencl_ctx *ctx);

/*
void		ftgr_clear_window(t_ftgr_ctx *xvar, t_ftgr_win *win);


bool		ftgr_is_key_down(t_ftgr_ctx *ctx);
bool		ftgr_is_key_up(t_ftgr_ctx *ctx);
void		ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active);

t_iv2		ftgr_get_screen_size(t_ftgr_ctx *ctx);
*/

#endif
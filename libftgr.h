/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:46 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/14 02:20:08 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTGR_H
#define LIBFTGR_H

#include "libft/std.h"
#include "libft/strings.h"
#include "libft/maths.h"
#include "srcs/libftgr_constants.h"

#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

#ifndef T_FTGR_CTX
typedef void *t_ftgr_ctx;
#define T_FTGR_CTX
#endif

#ifndef T_FTGR_WIN
typedef void *t_ftgr_win;
#define T_FTGR_WIN
#endif

typedef struct
{
	U64 line_size;
	U64 pixel_size;
	char *data;
	U64 data_size;
	t_iv2 size;

	t_ftgr_ctx *ctx;
	void *internal;
} t_ftgr_img;

typedef struct
{
	U8 r;
	U8 g;
	U8 b;
	U8 a;
} t_color;

#define COL_BLACK ((t_color){0, 0, 0, 255})
#define COL_WHITE ((t_color){255, 255, 255, 255})

#define COL_RED ((t_color){255, 0, 0, 255})
#define COL_LIGHT_RED ((t_color){255, 74, 74, 255})
#define COL_DARK_RED ((t_color){127, 0, 0, 255})

#define COL_GREEN ((t_color){0, 255, 0, 255})
#define COL_LIGHT_GREEN ((t_color){74, 255, 74, 255})
#define COL_DARK_GREEN ((t_color){0, 127, 0, 255})

#define COL_BLUE ((t_color){0, 0, 255, 255})
#define COL_LIGHT_BLUE ((t_color){74, 74, 255, 255})
#define COL_DARK_BLUE ((t_color){0, 0, 127, 255})

#define COL_GRAY ((t_color){127, 127, 127, 255})
#define COL_LIGHT_GRAY ((t_color){190, 190, 190, 255})
#define COL_DARK_GRAY ((t_color){63, 63, 63, 255})


t_ftgr_ctx *ftgr_create_ctx();
bool ftgr_wait(t_ftgr_ctx *ctx);
bool ftgr_poll(t_ftgr_ctx *ctx);

t_ftgr_win *ftgr_new_window(t_ftgr_ctx *ctx, t_iv2 size, const_string title);
void ftgr_free_window(t_ftgr_win *win);
void ftgr_set_win_name(t_ftgr_win *win, string name);
void ftgr_set_win_name_infos(t_ftgr_win *win, string infos);

void ftgr_free(t_ftgr_ctx *ctx);

void ftgr_bring_top(t_ftgr_win *win);

void ftgr_mouse_move(t_ftgr_ctx *ctx, t_ftgr_win *win, t_iv2 pos);
void ftgr_mouse_hide(t_ftgr_ctx *ctx, t_ftgr_win *win);
void ftgr_mouse_show(t_ftgr_ctx *ctx, t_ftgr_win *win);
t_iv2 ftgr_mouse_get_pos(t_ftgr_ctx *ctx, t_ftgr_win *win);
bool ftgr_mouse_pressed(t_ftgr_ctx *ctx, S32 button);
bool ftgr_mouse_click(t_ftgr_ctx *ctx, S32 button);

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

t_color ftgr_rand_color();

void ftgr_display_fps(t_ftgr_win *win);
S32 ftgr_color_to_int(t_color col);


void ftgr_draw_line(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_color col);
void ftgr_draw_line_e(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p));

void ftgr_draw_rect(t_ftgr_img *img, t_iv2 c1, t_iv2 c2, t_color col);
void ftgr_draw_rect_e(t_ftgr_img *img, t_iv2 c1, t_iv2 c2, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p));

void ftgr_fill_rect(t_ftgr_img *img, t_iv2 c1, t_iv2 c2, t_color col);
void ftgr_fill_rect_e(t_ftgr_img *img, t_iv2 c1, t_iv2 c2, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p));

/*
void		ftgr_clear_window(t_ftgr_ctx *xvar, t_ftgr_win *win);


bool		ftgr_is_key_down(t_ftgr_ctx *ctx);
bool		ftgr_is_key_up(t_ftgr_ctx *ctx);
void		ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active);

t_iv2		ftgr_get_screen_size(t_ftgr_ctx *ctx);
*/

#endif
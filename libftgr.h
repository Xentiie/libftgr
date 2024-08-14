/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:46 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/10 00:17:09 by reclaire         ###   ########.fr       */
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

#define FTGR_EX11 1000

typedef struct s_ftgr_ctx t_ftgr_ctx;
typedef struct s_ftgr_win t_ftgr_win;
typedef struct s_ftgr_img t_ftgr_img;
typedef struct s_color t_color;
typedef struct s_widget t_widget;
typedef struct s_bitmap t_bitmap;
typedef struct s_bitmap_text_infos t_bitmap_text_infos;
typedef struct s_label_widget t_label_widget;

struct s_ftgr_win 
{
	t_ftgr_ctx *ctx;

	t_ftgr_img *surface;

	S32 cursor_mode;
	string name;
	t_iv2 size;
	void *internal;
	t_widget *w_root;
};

struct s_ftgr_img
{
	U8 bpp;
	U64 line_size;
	char *data;
	U64 data_size;
	t_iv2 size;
};

struct s_color
{
	U8 r;
	U8 g;
	U8 b;
	U8 a;
};

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
void ftgr_move_window(t_ftgr_win *win, t_iv2 pos);
void ftgr_swap_buffers(t_ftgr_win *win);

void ftgr_free(t_ftgr_ctx *ctx);

void ftgr_bring_top(t_ftgr_win *win);

void ftgr_mouse_move(t_ftgr_ctx *ctx, t_ftgr_win *win, t_iv2 pos);
void ftgr_mouse_hide(t_ftgr_ctx *ctx, t_ftgr_win *win);
void ftgr_mouse_show(t_ftgr_ctx *ctx, t_ftgr_win *win);
t_iv2 ftgr_mouse_get_pos(t_ftgr_ctx *ctx, t_ftgr_win *win);
t_iv2 ftgr_mouse_get_raw_pos(t_ftgr_ctx *ctx);
bool ftgr_mouse_pressed(t_ftgr_ctx *ctx, S32 button);
bool ftgr_mouse_down(t_ftgr_ctx *ctx, S32 button);
bool ftgr_mouse_released(t_ftgr_ctx *ctx, S32 button);

bool ftgr_is_key_pressed(t_ftgr_ctx *ctx, U8 key);
bool ftgr_is_key_down(t_ftgr_ctx *ctx, U8 key);
bool ftgr_is_key_up(t_ftgr_ctx *ctx, U8 key);
void ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active);

void ftgr_set_error_callback(t_ftgr_ctx *ctx, void (*callback)());

float ftgr_time(t_ftgr_ctx *ctx);
float ftgr_delta_time(t_ftgr_ctx *ctx);

t_ftgr_img *ftgr_new_img(t_ftgr_ctx *ctx, t_iv2 size);
void ftgr_free_img(t_ftgr_img *img);
void ftgr_display_image(t_ftgr_img *img, t_ftgr_win *win, t_iv2 pos);

t_color ftgr_rand_color(U32 ofs);

void ftgr_display_fps(t_ftgr_win *win);
U32 ftgr_color_to_int(t_color col);
t_color ftgr_int_to_color(U32 v);

#define ftgr_get_pixel_addr(image, x, y) (img->data + ((y) * img->line_size + (x) * img->bpp))
t_color ftgr_get_pixel(t_ftgr_img *img, t_iv2 p);
void ftgr_set_pixel(t_ftgr_img *img, t_iv2 p, t_color col);
void ftgr_draw_line(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_color col);
void ftgr_draw_line_e(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p));
void ftgr_draw_line_horizontal(t_ftgr_img *img, t_iv2 p1, S32 x2, t_color col);
void ftgr_draw_bezier(t_ftgr_img *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res);
void ftgr_draw_rect(t_ftgr_img *img, t_iv4 rect, t_color col);
void ftgr_draw_rect_e(t_ftgr_img *img, t_iv4 rect, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p));
void ftgr_fill_rect(t_ftgr_img *img, t_iv4 rect, t_color col);
void ftgr_fill_rect_e(t_ftgr_img *img, t_iv4 rect, t_color (*eval)(t_iv2 p1, t_iv2 p2, t_iv2 p));
void ftgr_draw_circle(t_ftgr_img *img, t_iv2 pos, S32 radius, t_color col);
void ftgr_draw_disc(t_ftgr_img *img, t_iv2 pos, S32 radius, t_color col);
void ftgr_stretch_img(t_ftgr_img *dst, t_iv4 dst_rect, t_ftgr_img *src, t_iv4 src_rect);
void ftgr_stretch_img2(t_ftgr_img *dst, t_iv4 dst_rect, t_iv4 dst_rect_st_nd, t_ftgr_img *src, t_iv4 src_rect);
void ftgr_cpy_img(t_ftgr_img *dst, t_iv2 dst_pos, t_ftgr_img *src, t_iv4 src_rect);

void *ftgr_load_font(file fd, t_ftgr_img *img);
t_ftgr_img *ftgr_load_png(t_ftgr_ctx *ctx, const_string path);

typedef void (t_widget_drawer_draw_f)(t_ftgr_img *out, t_widget *widget, void *data);
typedef struct s_widget_drawer
{
	void *data;
	bool cleanup_data;
	t_widget_drawer_draw_f *draw_f;
} t_widget_drawer;

/*
              root
			 /    \
		    /      \
		child1   child2
		/  |  \
	   /   |   \
	  /    |    \
	 /     |     \
  elem1  elem2  elem3

root = {
	.childrens=[
		child1={
			.childrens=[
				elem1={
					.childrens=NULL
					.next=NULL
				},
				elem2={
					.childrens=NULL
					.next=NULL
				},
				elem3={
					.childrens=NULL
					.next=NULL
				}
			]
			.next=child2
		},
		child2={
			.childrens=NULL
			.next=NULL
		}
	]
	.next = NULL

}
*/
struct s_widget_callback
{
	void (*f)(void *data);
	void *data;
};
typedef struct s_widget
{
	U8 drawers_n;
	t_widget_drawer drawers[4];
	t_iv2 pos;
	t_iv2 size;
	bool capture_input;
	struct s_widget *last;
	struct s_widget *childrens;
	struct s_widget *next;
	struct s_widget *master;

	struct s_widget_callback on_cursor_move;
	struct s_widget_callback on_cursor_click;
	struct s_widget_callback on_cursor_release;
	struct s_widget_callback on_cursor_enter;
	struct s_widget_callback on_cursor_exit;
} t_widget;

void ftgr_redraw_rect(t_ftgr_win *win, t_iv4 rect);

t_widget *ftgr_new_widget();
void ftgr_init_widget(t_widget *widget);
void ftgr_free_widget_recursive(t_widget *widget);
void ftgr_free_widget(t_widget *widget);

void ftgr_add_widget(t_widget *widget, t_widget *master);
void ftgr_remove_widget(t_widget *widget);

void ftgr_draw_widget(t_ftgr_img *out, t_widget *widget);
void ftgr_draw_widget_recursive(t_ftgr_img *out, t_widget *widget);

bool ftgr_wdrawer_copy_img_cpu(t_widget *widget, t_ftgr_img *img);
bool ftgr_wdrawer_stretch_img_cpu(t_widget *widget, t_ftgr_img *img);
bool ftgr_wdrawer_paint_rect(t_widget *widget, t_color *color);
bool ftgr_wdrawer_bitmap_text(t_widget *widget, t_bitmap_text_infos *infos);



struct s_bitmap
{
	t_ftgr_img *img;
	U32 char_width;
	U32 char_height;
	U32 sep_width;
	U32 sep_height;
	U32 line_width;
};

struct s_bitmap_text_infos
{
	t_bitmap *bitmap;
	string text;
	S32 scale;
	t_iv2 kerning;
};

void ftgr_init_bitmap(t_bitmap *bitmap, t_ftgr_img *img, t_iv2 char_size, U32 line_chars_count, t_iv2 sep_size);
t_iv4 ftgr_bitmap_rect_char_lines(t_bitmap *bitmap, t_iv2 pos, U32 line_width, U32 lines_cnt);
U64 ftgr_bitmap_get_width(t_bitmap *bitmap, U32 kerning, string text);
void ftgr_draw_bitmap_text(t_ftgr_img *out, t_iv4 rect, t_bitmap_text_infos infos);

struct s_label_widget
{
	t_widget widget;
	t_bitmap *bitmap;
	t_bitmap_text_infos infos;
};

t_label_widget *ftgr_label_widget(t_bitmap *bitmap);
void ftgr_label_update(t_label_widget *label, string text);

/*
void		ftgr_clear_window(t_ftgr_ctx *xvar, t_ftgr_win *win);


bool		ftgr_is_key_down(t_ftgr_ctx *ctx);
bool		ftgr_is_key_up(t_ftgr_ctx *ctx);
void		ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active);

t_iv2		ftgr_get_screen_size(t_ftgr_ctx *ctx);
*/

#endif

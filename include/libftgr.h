/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:46 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/07 15:25:27 by reclaire         ###   ########.fr       */
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

/* any shift key */
#define FTGR_KEYMOD_SHIFT (1 << 1)
/* any control key */
#define FTGR_KEYMOD_CONTROL (1 << 2)
/* any alt key */
#define FTGR_KEYMOD_ALT (1 << 3)
/* windows key / 'command' mac key */
#define FTGR_KEYMOD_SUPER (1 << 4)
/* capslock on */
#define FTGR_KEYMOD_CAPSLOCK (1 << 5)
/* numlock on */
#define FTGR_KEYMOD_NUMLOCK (1 << 6)

#define FTGR_EX11 1000

#define SWAP(x, y)               \
	do                           \
	{                            \
		typeof(x) __tmp_var = x; \
		x = y;                   \
		y = __tmp_var;           \
	} while (0)

typedef struct s_ftgr_ctx t_ftgr_ctx;
typedef struct s_ftgr_win t_ftgr_win;
typedef struct s_ftgr_img t_ftgr_img;
typedef struct s_color t_color;
typedef struct s_widget t_widget;
typedef struct s_bitmap t_bitmap;
typedef struct s_text t_text;
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
	U8 *data;
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
void ftgr_free(t_ftgr_ctx *ctx);

/*
Wait for an event to happen, then process it and return TRUE. The application will hang while waiting.
Returns FALSE if the application should quit.
*/
bool ftgr_wait(t_ftgr_ctx *ctx);
/*
Process all events currently queued, then return TRUE.
Returns FALSE if the application should quit.
*/
bool ftgr_poll(t_ftgr_ctx *ctx);

t_ftgr_win *ftgr_new_window(t_ftgr_ctx *ctx, t_iv2 size, const_string title);
void ftgr_free_window(t_ftgr_win *win);
void ftgr_bring_top(t_ftgr_win *win);
void ftgr_set_win_name(t_ftgr_win *win, string name);
/* Copies the string `infos` after the window's name */
void ftgr_set_win_name_infos(t_ftgr_win *win, string infos);
void ftgr_move_window(t_ftgr_win *win, t_iv2 pos);
/* Swaps the front and back buffer of the window, copying the previous back buffer to the window */
void ftgr_swap_buffers(t_ftgr_win *win);

void ftgr_mouse_move(t_ftgr_ctx *ctx, t_ftgr_win *win, t_iv2 pos);
void ftgr_mouse_hide(t_ftgr_ctx *ctx, t_ftgr_win *win);
void ftgr_mouse_show(t_ftgr_ctx *ctx, t_ftgr_win *win);
/* `win` can be NULL to retrieve the absolute mouse position */
t_iv2 ftgr_mouse_get_pos(t_ftgr_ctx *ctx, t_ftgr_win *win);
/* Returns TRUE if the specified mouse button is currently pressed */
bool ftgr_mouse_pressed(t_ftgr_ctx *ctx, S32 button);
/* Returns TRUE if the specified mouse button has been pressed this frame */
bool ftgr_mouse_down(t_ftgr_ctx *ctx, S32 button);
bool ftgr_mouse_released(t_ftgr_ctx *ctx, S32 button);

/* Returns TRUE if the specified key is currently pressed */
bool ftgr_is_key_pressed(t_ftgr_ctx *ctx, U8 key);
/* Returns TRUE if the specified key has been pressed this frame */
bool ftgr_is_key_down(t_ftgr_ctx *ctx, U8 key);
bool ftgr_is_key_up(t_ftgr_ctx *ctx, U8 key);
void ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active);

/* Not used */
void ftgr_set_error_callback(t_ftgr_ctx *ctx, void (*callback)());

/* Returns the time since application start */
float ftgr_time(t_ftgr_ctx *ctx);
/* Returns the time elapsed for last frame */
float ftgr_delta_time(t_ftgr_ctx *ctx);

/* Creates a new RGBA image */
t_ftgr_img *ftgr_new_img(t_ftgr_ctx *ctx, t_iv2 size);
void ftgr_free_img(t_ftgr_img *img);
/* Copies the image `img` to the window's back buffer */
void ftgr_display_image(t_ftgr_img *img, t_ftgr_win *win, t_iv2 pos);

/* Returns a random color from `seed` */
t_color ftgr_rand_color(U32 seed);
/* Blends 2 colors using the alpha channel */
t_color ftgr_alpha_blend(t_color under, t_color over);

/* Displays the FPS in the window's info */
void ftgr_display_fps(t_ftgr_win *win);
/* Encodes a color into a U32 */
U32 ftgr_color_to_int(t_color col);
/* Decodes a U32 to a color */
t_color ftgr_int_to_color(U32 v);

/* Returns the address of a specific pixel in an image. `img` should be of type `t_ftgr_img`, and `x` and `y` should be any non-float scalar */
#define ftgr_get_pixel_addr(img, x, y) ((img)->data + ((y) * (img)->line_size + (x) * (img)->bpp))
t_color ftgr_get_pixel(t_ftgr_img *img, t_iv2 p);
void ftgr_set_pixel(t_ftgr_img *img, t_iv2 p, t_color col);
void ftgr_draw_line(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_color col);
void ftgr_draw_line_e(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_iv4 lp1lp2, void *data), void *data);
void ftgr_draw_line_horizontal(t_ftgr_img *img, t_iv2 p1, S32 x2, t_color col);
void ftgr_draw_line_horizontal_e(t_ftgr_img *img, t_iv2 p1, S32 x2, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_iv4 lp1lp2, void *data), void *data);
void ftgr_draw_line_vertical(t_ftgr_img *img, t_iv2 p1, S32 y2, t_color col);
void ftgr_draw_line_vertical_e(t_ftgr_img *img, t_iv2 p1, S32 y2, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_iv4 lp1lp2, void *data), void *data);
void ftgr_draw_bezier(t_ftgr_img *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res);
void ftgr_draw_rect(t_ftgr_img *img, t_iv4 rect, t_color col);
void ftgr_draw_rect_e(t_ftgr_img *img, t_iv4 rect, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_iv4 rect, void *data), void *data);
void ftgr_fill_rect(t_ftgr_img *img, t_iv4 rect, t_color col);
void ftgr_fill_rect_e(t_ftgr_img *img, t_iv4 rect, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_iv4 rect, void *data), void *data);
void ftgr_draw_triangle(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col);
void ftgr_draw_triangle_e(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_v3 w, void *data), void *data);
void ftgr_fill_triangle_e(t_ftgr_img *img, t_iv2 ip1, t_iv2 ip2, t_iv2 ip3, void (*eval)(t_ftgr_img *img, t_iv2 xy, t_v3 w, void *data), void *data);
void ftgr_draw_circle(t_ftgr_img *img, t_iv2 pos, S32 radius, t_color col);
void ftgr_draw_disc(t_ftgr_img *img, t_iv2 pos, S32 radius, t_color col);
void ftgr_stretch_img(t_ftgr_img *dst, t_iv4 dst_rect, t_ftgr_img *src, t_iv4 src_rect);
void ftgr_stretch_img2(t_ftgr_img *dst, t_iv4 dst_rect, t_ftgr_img *src, t_iv4 src_rect, t_color col);
void ftgr_cpy_img(t_ftgr_img *dst, t_iv2 dst_pos, t_ftgr_img *src, t_iv4 src_rect);

void *ftgr_load_font(file fd, t_ftgr_img *img);
t_ftgr_img *ftgr_load_png(t_ftgr_ctx *ctx, const_string path);

/* 32 bytes of user-data for a t_widget */
union u_widget_data
{
	U8 u8[32];
	U16 u16[16];
	U32 u32[8];
	U64 u64[4];

	t_iv2 iv2[4];
	t_iv3 iv3[2];
	t_iv4 iv4[2];

	void *ptr[4];

	t_ftgr_img *img[4];
	t_color color[8];
};
typedef void(t_widget_drawer_draw_f)(t_ftgr_img *out, t_widget *widget, t_iv2 abs_pos, union u_widget_data data);
typedef struct s_widget_drawer
{
	t_widget_drawer_draw_f *draw_f;
	union u_widget_data data;
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

typedef bool (*t_widget_callback)(t_widget *widget, t_iv2 cursor_pos);
typedef struct s_widget
{
	U8 drawers_n;
	U64 drawers_alloc;
	t_widget_drawer *drawers;
	t_iv2 pos;
	t_iv2 size;
	bool handle_input;	// Does this widget receives inputs events
	bool capture_input; // Does this widget captures inputs events (doesn't pass them down to childrens)
	struct s_widget *master;
	struct s_widget *next;
	struct s_widget *childrens;
	struct s_widget *last;

	union u_widget_data data;
	string name; // optional, can be NULL

	t_widget_callback on_cursor_move;
	t_widget_callback on_cursor_click;
	t_widget_callback on_cursor_release;
	t_widget_callback on_cursor_enter;
	t_widget_callback on_cursor_exit;

	bool hovered;
	bool clicked;

} t_widget;

void ftgr_redraw_rect(t_ftgr_win *win, t_iv4 rect);

t_widget *ftgr_new_widget();
bool ftgr_init_widget(t_widget *widget);
void ftgr_free_widget_recursive(t_widget *widget);
void ftgr_free_widget(t_widget *widget);
bool ftgr_add_wdrawer(t_widget *widget, t_widget_drawer drawer);

void ftgr_add_widget(t_widget *widget, t_widget *master);
void ftgr_remove_widget(t_widget *widget);

void ftgr_handle_widget_events(t_ftgr_win *win, t_widget *w);

void ftgr_draw_widget(t_ftgr_img *out, t_widget *widget);
void ftgr_draw_widget_recursive(t_ftgr_img *out, t_widget *widget);

t_iv2 ftgr_widget_abs_pos(t_widget *widget);

/* widgets drawers */
bool ftgr_wdrawer_copy_img_cpu(t_widget *widget, t_ftgr_img *img);
bool ftgr_wdrawer_stretch_img_cpu(t_widget *widget, t_ftgr_img *img);
bool ftgr_wdrawer_paint_rect(t_widget *widget, t_color color);
bool ftgr_wdrawer_draw_rect(t_widget *widget, t_color color);

/* bitmaps */
struct s_bitmap
{
	t_ftgr_img *img;
	U32 char_width;
	U32 char_height;
	U32 sep_width;
	U32 sep_height;
	U32 line_width;
};

struct s_text
{
	string str;
	S32 scale;
	t_iv2 kerning;
};

void ftgr_init_bitmap(t_bitmap *bitmap, t_ftgr_img *img, t_iv2 char_size, U32 line_chars_count, t_iv2 sep_size);
t_iv4 ftgr_bitmap_rect_char_lines(t_bitmap *bitmap, t_iv2 pos, U32 line_width, U32 lines_cnt);
U64 ftgr_bitmap_get_width(t_bitmap *bitmap, t_text text);
U64 ftgr_bitmap_get_height(t_bitmap *bitmap, t_text text);
void ftgr_draw_bitmap_text(t_ftgr_img *out, t_iv4 rect, t_bitmap *bitmap, t_text text, t_color col);

/*
void		ftgr_clear_window(t_ftgr_ctx *xvar, t_ftgr_win *win);


bool		ftgr_is_key_down(t_ftgr_ctx *ctx);
bool		ftgr_is_key_up(t_ftgr_ctx *ctx);
void		ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active);

t_iv2		ftgr_get_screen_size(t_ftgr_ctx *ctx);
*/

#endif

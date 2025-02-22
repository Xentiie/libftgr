/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:46 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/14 03:07:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTGR_H
#define LIBFTGR_H

#include "libft/std.h"
#include "libft/strings.h"
#include "libft/images.h"
#include "libft/maths.h"

#define FTGR_CURSOR_NORMAL (0)
#define FTGR_CURSOR_LOCKED (1 << 0)
#define FTGR_CURSOR_HIDDEN (1 << 1)

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

typedef struct s_ftgr_ctx t_ftgr_ctx;
typedef struct s_ftgr_win t_ftgr_win;
typedef union u_color t_color;
typedef struct s_bitmap t_bitmap;
typedef struct s_text t_text;

struct s_ftgr_win
{
	t_ftgr_ctx *ctx;

	t_image *surface;

	S32 cursor_mode;
	string name;
	t_iv2 size;
	void *internal;

	t_iv2 last_mouse_pos;
};

#define ftgr_color(_r, _g, _b, _a) ((t_color){.r = (_r), .g = (_g), .b = (_b), .a = (_a)})
#define COL_BLACK ftgr_color(0, 0, 0, 255)
#define COL_WHITE ftgr_color(255, 255, 255, 255)

#define COL_RED ftgr_color(255, 0, 0, 255)
#define COL_LIGHT_RED ftgr_color(255, 74, 74, 255)
#define COL_DARK_RED ftgr_color(127, 0, 0, 255)

#define COL_GREEN ftgr_color(0, 255, 0, 255)
#define COL_LIGHT_GREEN ftgr_color(74, 255, 74, 255)
#define COL_DARK_GREEN ftgr_color(0, 127, 0, 255)

#define COL_BLUE ftgr_color(0, 0, 255, 255)
#define COL_LIGHT_BLUE ftgr_color(74, 74, 255, 255)
#define COL_DARK_BLUE ftgr_color(0, 0, 127, 255)

#define COL_GRAY ftgr_color(127, 127, 127, 255)
#define COL_LIGHT_GRAY ftgr_color(190, 190, 190, 255)
#define COL_DARK_GRAY ftgr_color(63, 63, 63, 255)

t_ftgr_ctx *ftgr_new_ctx();
void ftgr_destroy(t_ftgr_ctx *ctx);

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
void ftgr_blt_screen(t_ftgr_win *win);
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

/* Returns the time since application start */
float ftgr_time(t_ftgr_ctx *ctx);
/* Returns the time elapsed for last frame */
float ftgr_delta_time(t_ftgr_ctx *ctx);

/* Creates a new RGBA image */
t_image *ftgr_new_img(t_iv2 size);
/* Initalizes an image */
bool ftgr_init_img(t_image *img, t_iv2 size);
void ftgr_free_img(t_image *img);
/* Copies the image `img` to the window's back buffer */
void ftgr_display_image(t_image *img, t_ftgr_win *win, t_iv2 pos);

/* Displays the FPS in the window's info */
void ftgr_display_fps(t_ftgr_win *win);

/* Returns the address of a specific pixel in an image. `img` should be of type `t_image` */
#define ftgr_get_pixel(img, _x, _y) ((img)->pixels + ((_y) * ((img)->size.x) + (_x)))

/* Returns a random color from `seed` */
t_color ftgr_rand_color(U32 seed);
/* Blends 2 colors using the alpha channel */
t_color ftgr_alpha_blend(t_color under, t_color over);

/* lines */
/* draws a line between `p1` and `p2`, bounded by `img->size` */
void ftgr_draw_line(t_image *img, t_iv2 p1, t_iv2 p2, t_color col);
/* draws a line between `p1` and `p2`, bounded by `img->size` and `bound` */
void ftgr_draw_line_bound(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, t_iv4 bound);
/* draws an alpha blended line between `p1` and `p2`, bounded by `img->size` */
void ftgr_draw_line2(t_image *img, t_iv2 p1, t_iv2 p2, t_color col);
/* draws an alpha blended line between `p1` and `p2`, bounded by `img->size` and `bound` */
void ftgr_draw_line_bound2(t_image *img, t_iv2 p1, t_iv2 p2, t_color col, t_iv4 bound);

/* draws an horizontal line between `p1.x` and `x2`, bounded by `img->size` */
void ftgr_draw_line_horizontal(t_image *img, t_iv2 p1, S32 x2, t_color col);
/* draws an horizontal line between `p1.x` and `x2`, bounded by `img->size` and `bound` */
void ftgr_draw_line_horizontal_bound(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound);
/* draws an alpha blended horizontal line between `p1.x` and `x2`, bounded by `img->size` */
void ftgr_draw_line_horizontal2(t_image *img, t_iv2 p1, S32 x2, t_color col);
/* draws an alpha blended horizontal line between `p1.x` and `x2`, bounded by `img->size` and `bound` */
void ftgr_draw_line_horizontal_bound2(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound);

/* draws an vertical line between `p1.x` and `x2`, bounded by `img->size` */
void ftgr_draw_line_vertical(t_image *img, t_iv2 p1, S32 x2, t_color col);
/* draws an vertical line between `p1.x` and `x2`, bounded by `img->size` and `bound` */
void ftgr_draw_line_vertical_bound(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound);
/* draws an alpha blended vertical line between `p1.x` and `x2`, bounded by `img->size` */
void ftgr_draw_line_vertical2(t_image *img, t_iv2 p1, S32 x2, t_color col);
/* draws an alpha blended vertical line between `p1.x` and `x2`, bounded by `img->size` and `bound` */
void ftgr_draw_line_vertical_bound2(t_image *img, t_iv2 p1, S32 x2, t_color col, t_iv4 bound);

/* bezier */
/* draws a bezier curve between `p1`, `p2` and `p3`, with resolution `res`, bounded by `img->size` */
void ftgr_draw_bezier(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res);
/* draws a bezier curve between `p1`, `p2` and `p3`, with resolution `res`, bounded by `img->size` and `bound` */
void ftgr_draw_bezier_bound(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res, t_iv4 bound);
/* draws an alpha blended bezier curve between `p1`, `p2` and `p3`, with resolution `res`, bounded by `img->size` */
void ftgr_draw_bezier2(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res);
/* draws an alpha blended bezier curve between `p1`, `p2` and `p3`, with resolution `res`, bounded by `img->size` and `bound` */
void ftgr_draw_bezier_bound2(t_image *img, t_color col, t_v2 p1, t_v2 p2, t_v2 p3, S32 res, t_iv4 bound);

/* rects */
/* draws a rect `rect`, bounded by `img->size` */
void ftgr_draw_rect(t_image *img, t_iv4 rect, t_color col);
/* draws a rect `rect`, bounded by `img->size` and `bound` */
void ftgr_draw_rect_bound(t_image *img, t_iv4 rect, t_color col, t_iv4 bound);
/* draws an alpha blended rect `rect`, bounded by `img->size` */
void ftgr_draw_rect2(t_image *img, t_iv4 rect, t_color col);
/* draws an alpha blended rect `rect`, bounded by `img->size` and `bound` */
void ftgr_draw_rect_bound2(t_image *img, t_iv4 rect, t_color col, t_iv4 bound);

/* fills a rect `rect`, bounded by `img->size` */
void ftgr_fill_rect(t_image *img, t_iv4 rect, t_color col);
/* fills a rect `rect`, bounded by `img->size` and `bound` */
void ftgr_fill_rect_bound(t_image *img, t_iv4 rect, t_color col, t_iv4 bound);
/* fills an alpha blended rect `rect`, bounded by `img->size` */
void ftgr_fill_rect2(t_image *img, t_iv4 rect, t_color col);
/* fills an alpha blended rect `rect`, bounded by `img->size` and `bound` */
void ftgr_fill_rect_bound2(t_image *img, t_iv4 rect, t_color col, t_iv4 bound);

/* draws a triangle `p1`, `p2`, `p3`, bounded by `img->size` */
void ftgr_draw_triangle(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col);
/* draws a triangle `p1`, `p2`, `p3`, bounded by `img->size` and `bound` */
void ftgr_draw_triangle_bound(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col, t_iv4 bound);
/* draws an alpha blended triangle `p1`, `p2`, `p3`, bounded by `img->size` */
void ftgr_draw_triangle2(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col);
/* draws an alpha blended triangle `p1`, `p2`, `p3`, bounded by `img->size` and `bound` */
void ftgr_draw_triangle_bound2(t_image *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col, t_iv4 bound);

/* draws a disc at `pos` with radius `radius`, `p3`, bounded by `img->size` */
void ftgr_draw_disc(t_image *img, t_iv2 pos, S32 radius, t_color col);
/* draws a disc at `pos` with radius `radius`, `p3`, bounded by `img->size` and `bound` */
void ftgr_draw_disc_bound(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);
/* draws an alpha blended disc at `pos` with radius `radius`, `p3`, bounded by `img->size` */
void ftgr_draw_disc2(t_image *img, t_iv2 pos, S32 radius, t_color col);
/* draws an alpha blended disc at `pos` with radius `radius`, `p3`, bounded by `img->size` and `bound` */
void ftgr_draw_disc_bound2(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);

/* draws a circle at `pos` with radius `radius`, `p3`, bounded by `img->size` */
void ftgr_draw_circle(t_image *img, t_iv2 pos, S32 radius, t_color col);
/* draws a circle at `pos` with radius `radius`, `p3`, bounded by `img->size` and `bound` */
void ftgr_draw_circle_bound(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);
/* draws an alpha blended circle at `pos` with radius `radius`, `p3`, bounded by `img->size` */
void ftgr_draw_circle2(t_image *img, t_iv2 pos, S32 radius, t_color col);
/* draws an alpha blended circle at `pos` with radius `radius`, `p3`, bounded by `img->size` and `bound` */
void ftgr_draw_circle_bound2(t_image *img, t_iv2 pos, S32 radius, t_color col, t_iv4 bound);

void ftgr_stretch_img(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect);
void ftgr_stretch_img2(t_image *dst, t_iv4 dst_rect, t_image *src, t_iv4 src_rect, t_color col);
void ftgr_cpy_img(t_image *dst, t_iv2 dst_pos, t_image *src, t_iv4 src_rect);

void *ftgr_load_font(filedesc fd, t_image *img);
t_image *ftgr_load_png(const_string path);

/* bitmaps */
struct s_bitmap
{
	t_image *img;
	U32 char_width;
	U32 char_height;
	U32 sep_width;
	U32 sep_height;
	U32 line_width;
};

void ftgr_init_bitmap(t_bitmap *bitmap, t_image *img, t_iv2 char_size, U32 line_chars_count, t_iv2 sep_size);
t_iv4 ftgr_bitmap_rect_char_lines(t_bitmap *bitmap, t_iv2 pos, U32 line_width, U32 lines_cnt);
void ftgr_draw_bitmap_text(t_image *out, t_iv4 rect, t_bitmap *bitmap, string str, F32 scale, t_iv2 kerning, t_color col);

void DBGUI_events(t_ftgr_ctx *ctx);
void DBGUI_begin(t_iv2 mouse_pos);

void DBGUI_style_color_push(t_color col);
void DBGUI_style_color_pop();
void DBGUI_style_indent_push(S32 indent);
void DBGUI_style_indent_pop();
void DBGUI_style_vert_space(S32 size);

void DBGUI_begin_frame(t_color col);
void DBGUI_end_frame();

void DBGUI_text(const_string fmt, ...);
void DBGUI_img(t_image *img);

bool DBGUI_button(string fmt, ...);
bool DBGUI_checkbox(bool *on, string fmt, ...);
bool DBGUI_slider(F64 *value, F64 min, F64 max, string fmt, ...);

void DBGUI_render(t_image *img);

/*
void		ftgr_clear_window(t_ftgr_ctx *xvar, t_ftgr_win *win);


bool		ftgr_is_key_down(t_ftgr_ctx *ctx);
bool		ftgr_is_key_up(t_ftgr_ctx *ctx);
void		ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active);

t_iv2		ftgr_get_screen_size(t_ftgr_ctx *ctx);
*/

#endif

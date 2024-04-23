/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:46:17 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/10 10:53:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTGR_INT_H
#define FTGR_INT_H

#include "libft/std.h"
#include "libft/maths.h"
#include "libft/lists.h"
#include "libft/strings.h"
#include "libft/time.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <X11/XKBlib.h>

typedef struct
{
	bool up;
	bool down;
	U32 k;
} t_key;

typedef struct
{
	Display *display;
	Window root;
	Colormap cmap;
	Visual *visual;

	S32 screen;
	S32 depth;

	Atom del_win_atom;
	Atom protocols_atom;

	bool flush;
	bool use_xshm;

	S32 pixmap_shm_format;

	t_list *windows;

	float t_last_frame;
	float t_startup;

	t_time global_time;
	t_time delta_time_clk;
	float delta_time;

	t_list *keys;
} t_ftgr_ctx;

#define LIMIT_FREQ(secs, ...)                              \
	do                                                     \
	{                                                      \
		static t_time __freq_t1 = (t_time){0};             \
                                                           \
		t_time __freq_t2;                                  \
		clk_get(&__freq_t2);                               \
		if (clk_diff_float(&__freq_t1, &__freq_t2) < secs) \
			return __VA_ARGS__;                            \
                                                           \
		clk_get(&__freq_t1);                               \
	} while (0)

#define FTGR_WINDOW(lst) ((t_ftgr_win *)(lst->content))
#define FTGR_IMAGE_INT(img) ((t_ftgr_img_int *)(img->internal))
typedef struct
{
	t_ftgr_ctx *ctx;
	Window window;
	GC gc;
	string name;
} t_ftgr_win;

typedef struct
{
	U64 line_size;
	U64 pixel_size;
	char *data;
	t_iv2 size;

	t_ftgr_ctx *ctx;
	void *internal;
} t_ftgr_img;

typedef struct 
{
	Pixmap pixmap;
	XImage *img;
	GC gc;
	S32 format;
	bool shm;
} t_ftgr_img_int;

typedef struct {
	char r;
	char g;
	char b;
	char a;
}	t_color;


t_ftgr_ctx *ftgr_create_ctx();
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

void ftgr_set_error_callback(t_ftgr_ctx *ctx, void (*callback)());

float ftgr_time(t_ftgr_ctx *ctx);
float ftgr_delta_time(t_ftgr_ctx *ctx);

t_ftgr_img *ftgr_new_img(t_ftgr_ctx *ctx, t_iv2 size);
void ftgr_display_image(t_ftgr_img *img, t_ftgr_win *win, t_iv2 pos);
void ftgr_set_pixel(t_ftgr_img *img, t_iv2 p, t_color col);

void ftgr_display_fps(t_ftgr_win *win);
S32 ftgr_color_to_int(t_color col);

U32 _ftgr_keysym2uni(U32 keysym);
void _ftx11_keys_cleanup(t_ftgr_ctx *ctx);
void _ftx11_register_key_up(t_ftgr_ctx *ctx, U32 key);
void _ftx11_register_key_down(t_ftgr_ctx *ctx, U32 key);

#endif
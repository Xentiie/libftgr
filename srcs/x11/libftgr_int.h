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
#define T_FTGR_CTX
#define T_FTGR_WIN
#include "libftgr.h"

typedef struct 
{
	Pixmap pixmap;
	XImage *img;
	GC gc;
	S32 format;
	bool shm;
} t_ftgr_img_int;

U32 _ftgr_keysym2uni(U32 keysym);
void _ftx11_keys_cleanup(t_ftgr_ctx *ctx);
void _ftx11_register_key_up(t_ftgr_ctx *ctx, U32 key);
void _ftx11_register_key_down(t_ftgr_ctx *ctx, U32 key);

#endif
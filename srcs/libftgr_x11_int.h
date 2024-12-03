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

#ifndef LIBFTGR_X11_INT
#define LIBFTGR_X11_INT

#define _FT_RETURN TRUE

#include "libft/std.h"

#ifdef FT_OS_LINUX

#include "libft/maths.h"
#include "libft/lists.h"
#include "libft/strings.h"
#include "libft/time.h"
#include "libft/debug.h"

#include "libftgr.h"

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

typedef struct s_ftgr_ctx
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

	bool left_mouse_pressed, left_mouse_clicked, left_mouse_released;
	bool right_mouse_pressed, right_mouse_clicked, right_mouse_released;
	bool middle_mouse_pressed, middle_mouse_clicked, middle_mouse_released;

	t_list *keys;
} t_ftgr_ctx;

#define LIMIT_FREQ(secs, ...)                                 \
	do                                                        \
	{                                                         \
		static t_time __freq_t1 = (t_time){0};                \
                                                              \
		t_time __freq_t2;                                     \
		ft_clk_get(&__freq_t2);                               \
		if (ft_clk_diff_float(&__freq_t1, &__freq_t2) < secs) \
			return __VA_ARGS__;                               \
                                                              \
		ft_clk_get(&__freq_t1);                               \
	} while (0)

#define FTGR_WINDOW(lst) ((t_ftgr_win *)((lst)->content))
#define FTGR_WINDOW_INT(win) ((t_ftgr_win_int *)((win)->internal))

typedef struct
{
	Pixmap pixmap;
	XImage *ximage;
	GC gc;
	S32 format;
	bool shm;

	t_ftgr_img img;
} t_framebuffer_data;

typedef struct
{
	Window window;
	GC gc;
	string name;
	U8 front, back;
	t_framebuffer_data buffers[2];
} t_ftgr_win_int;

U32 _ftgr_keysym2uni(U32 keysym);
void _ftx11_keys_cleanup(t_ftgr_ctx *ctx);
void _ftx11_register_key_up(t_ftgr_ctx *ctx, U32 key);
void _ftx11_register_key_down(t_ftgr_ctx *ctx, U32 key);

#endif
#endif
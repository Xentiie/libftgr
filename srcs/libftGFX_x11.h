/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftGFX_x11.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:53:40 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/11 20:55:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIFBTGFX_X11_H)
#define LIFBTGFX_X11_H

#include "libft/std.h"

#if FT_OS_LINUX

#include "libft/maths.h"
#include "libft/lists.h"
#include "libft/strings.h"
#include "libft/time.h"
#include "libft/debug.h"
#include "libft/bits/ft_return.h"

#include "libftGFX.h"

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

struct s_ftGFX_ctx_private
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
};

#define FTGR_WINDOW_PRIVATE(win) ((t_ftGFX_win_private *)((win)->private))

struct s_framebuffer
{
	Pixmap xpixmap;
	XImage *ximage;
	S32 format;
	bool shm;

	t_image img;
};

struct s_ftGFX_window_private
{
	Window window;
	GC gc;

	struct s_framebuffer framebuffer;

	/* Blank cursor cache for ftGFX_mouse_hide */
	struct
	{
		bool has_blank_cursor;
		Pixmap pixmap;
		Cursor cursor;
	} blank_cursor;
};

/*
Converts a X11 mouse button number to a ftGFX mouse button number.
### On error
Returns `((U8)-1)` and sets ft_errno.
### ft_errno
- FT_ERANGE if no ftGFX button maps to the specified X11 button.
*/
U8 ftgfxx11_x11_to_ftgfx_mouse_button(U32 x11_mouse_button);

/* Initializes the blank cursor for the specified window. */
bool ftgfxx11_init_blank_cursor(struct s_ftGFX_window *win);
/* Destroys the blank cursor for the specified window. */
void ftgfxx11_destroy_blank_cursor(struct s_ftGFX_window *win);

U32 ftgfxx11_keysym_to_unicode(U32 keysym);

void ftgfxx11_keys_reset(struct s_ftGFX_ctx *ctx);

#endif
#endif
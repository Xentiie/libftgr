/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr_int_win.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 23:21:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 12:05:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTGR_WIN_INT
#define LIBFTGR_WIN_INT

#include "libft/std.h"

// Set to 0 to test performances later
#define CACHE_IMAGE_DC 1

#ifdef FT_OS_WIN

#include "libft/maths.h"
#include "libft/lists.h"
#include "libft/strings.h"
#include "libft/time.h"
#include "libftgr_constants.h"
#include <windows.h>
#include <stdio.h>

#include "libftgr.h"

typedef struct
{
	bool up;
	bool down;
	bool pressed;
	U8 k;
} t_key;

typedef struct s_ftgr_ctx
{
	HINSTANCE instance_handle;
	ATOM main_window_class;

	bool key_autorepeat;

	t_list *windows;

	t_time global_time;
	t_time delta_time_clk;
	float delta_time;

	t_key keys[256];

	bool left_mouse_pressed, left_mouse_clicked, left_mouse_released;
	bool right_mouse_pressed, right_mouse_clicked,  right_mouse_released;
	bool middle_mouse_pressed, middle_mouse_clicked, middle_mouse_released;

	t_widget *widget_root;
} t_ftgr_ctx;

typedef enum {
	IMAGE,
	WINDOW
}	e_surface_type;

#define MK_SURFACE() e_surface_type surface_type; HDC dc;
#define PEEK_SURFACE(x) (((t_surface*)x)->surface_type)
typedef struct s_surface
{
	MK_SURFACE();
}	t_surface;

typedef struct s_ftgr_win
{
	MK_SURFACE();
	t_ftgr_ctx *ctx;
	HWND window_handle;
	S32 cursor_mode;
	string name;
	t_iv2 size;
} t_ftgr_win;

#define FTGR_WINDOW_CLASS "FtMainWindowClass"
#define FTGR_PROP_NAME L"ftgr"

#define _ftgr_error() _ftgr_error(__FILE__, __LINE__)
#define CHECKRET(v) \
	if (!v)         \
		_ftgr_error();

typedef struct
{
	MK_SURFACE();
	HBITMAP bitmap;
} t_ftgr_img_int;

#define FTGR_WINDOW(lst) ((t_ftgr_win *)(lst->content))
#define FTGR_IMAGE_INT(img) ((t_ftgr_img_int *)(img->internal))
#define LIMIT_FREQ(secs, ...)                              \
	do                                                     \
	{                                                      \
		static t_time __freq_t1 = {0, 0};                  \
                                                           \
		t_time __freq_t2;                                  \
		clk_get(&__freq_t2);                               \
		if (clk_diff_float(&__freq_t1, &__freq_t2) < secs) \
			return __VA_ARGS__;                            \
                                                           \
		clk_get(&__freq_t1);                               \
	} while (0)

void(_ftgr_error)(char *file, int line);
void _ftwin32_keys_cleanup(t_ftgr_ctx *ctx);
void _ftwin32_register_key_up(t_ftgr_ctx *ctx, U8 key);
void _ftwin32_register_key_down(t_ftgr_ctx *ctx, U8 key);

#endif

#endif
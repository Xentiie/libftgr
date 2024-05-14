/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr_int.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 23:21:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 12:05:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef libftgr_int_H
#define libftgr_int_H

#include <windows.h>
#include <stdio.h>
#include "libft/std.h"
#include "libft/maths.h"
#include "libft/lists.h"
#include "libft/strings.h"
#include "libft/time.h"
#include "../libftgr_constants.h"

typedef struct s_ftgr_ctx
{
	HINSTANCE instance_handle;
	ATOM main_window_class;

	bool key_autorepeat;

	t_list *windows;

	t_time global_time;
	t_time delta_time_clk;
	float delta_time;

	t_list *keys;

	bool left_mouse_pressed, left_mouse_clicked;
	bool right_mouse_pressed, right_mouse_clicked;
	bool middle_mouse_pressed, middle_mouse_clicked;

	bool ui_focus;

} t_ftgr_ctx;

typedef struct s_ftgr_win
{
	t_ftgr_ctx *ctx;
	HWND window_handle;
	S32 cursor_mode;
	string name;
	HDC dc;
} t_ftgr_win;
#define T_FTGR_CTX
#define T_FTGR_WIN
#include "libftgr.h"

#define FTGR_WINDOW_CLASS "FtMainWindowClass"
#define FTGR_PROP_NAME L"ftgr"

#define _ftgr_error() _ftgr_error(__FILE__, __LINE__)
#define CHECKRET(v) \
	if (!v)         \
		_ftgr_error();

typedef struct
{
	bool up;
	bool down;
	U32 k;
} t_key;

typedef struct
{
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

void(_ftgr_error)();
void _ftwin32_keys_cleanup(t_ftgr_ctx *ctx);
void _ftwin32_register_key_up(t_ftgr_ctx *ctx, U32 key);
void _ftwin32_register_key_down(t_ftgr_ctx *ctx, U32 key);


typedef struct s_ui_element t_ui_element;
typedef void (*t_ui_callback)(t_ui_element *ui, void *param1, void *param2);

#define T_UI_ELEMENT
#define T_UI_CALLBACK
#include "libftgr_ui.h"

typedef struct s_ui_element
{
	t_list *callbacks[UI_EVENT_MAX];
	t_v2 pos;
	t_v2 size;
	t_ftgr_img *img;
	U32 flags;
}	t_ui_element;

#endif
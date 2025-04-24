/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:46 by reclaire          #+#    #+#             */
/*   Updated: 2025/03/06 18:08:59 by reclaire         ###   ########.fr       */
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
/* Draws the current window surface to the screen */
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

/* Displays the FPS in the window's info */
void ftgr_display_fps(t_ftgr_win *win);

void *ftgr_load_font(filedesc fd, t_image *img);

/*
void		ftgr_clear_window(t_ftgr_ctx *xvar, t_ftgr_win *win);


bool		ftgr_is_key_down(t_ftgr_ctx *ctx);
bool		ftgr_is_key_up(t_ftgr_ctx *ctx);
void		ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active);

t_iv2		ftgr_get_screen_size(t_ftgr_ctx *ctx);
*/

#endif

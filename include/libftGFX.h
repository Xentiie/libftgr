/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftGFX.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:46 by reclaire          #+#    #+#             */
/*   Updated: 2025/07/08 15:44:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFTGFX_H)
#define LIBFTGFX_H

#include "libftGFX/keys.h"

#include "libft/std.h"
#include "libft/strings.h"
#include "libft/time.h"
#include "libft/images.h"
#include "libft/maths.h"
#include "libft/io.h"

#include "libft/bits/static_array_len.h"

struct s_ftGFX_ctx;
struct s_ftGFX_ctx_private;
struct s_ftGFX_window;
struct s_ftGFX_window_private;

packed_enum e_ftGFX_mouse_button{
	FTGFX_MOUSE_LEFT,
	FTGFX_MOUSE_MIDDLE,
	FTGFX_MOUSE_RIGHT,
	FTGFX_MOUSE_SCROLLWHEEL_UP,
	FTGFX_MOUSE_SCROLLWHEEL_DOWN,
	FTGFX_MOUSE_SCROLLWHEEL_PUSH_LEFT,
	FTGFX_MOUSE_SCROLLWHEEL_PUSH_RIGHT,
	FTGFX_MOUSE_SIDE_1,
	FTGFX_MOUSE_SIDE_2,

	_FTGFX_MOUSE_MAX,
};

enum e_ftGFX_cursor
{
	FTGFX_CURSOR_BLANK,
	FTGFX_CURSOR_DEFAULT,

	FTGFX_CURSOR_TOP_SIDE,
	FTGFX_CURSOR_BOTTOM_SIDE,
	FTGFX_CURSOR_LEFT_SIDE,
	FTGFX_CURSOR_RIGHT_SIDE,
	FTGFX_CURSOR_TOP_LEFT_CORNER,
	FTGFX_CURSOR_TOP_RIGHT_CORNER,
	FTGFX_CURSOR_BOTTOM_LEFT_CORNER,
	FTGFX_CURSOR_BOTTOM_RIGHT_CORNER,

	FTGFX_CURSOR_TEXT,

	_FTGFX_CURSOR_MAX,
};

enum e_ftGFX_key_state
{
	/* Released this frame. */
	FTGFX_KEY_STATE_RELEASED = -1,
	/* Up state. */
	FTGFX_KEY_STATE_UP,
	/* Pressed this frame. */
	FTGFX_KEY_STATE_PRESSED,
	/* Down state. */
	FTGFX_KEY_STATE_DOWN,
};

#define FTGFX_MOUSE_STATE_RELEASED FTGFX_KEY_STATE_RELEASED
#define FTGFX_MOUSE_STATE_UP FTGFX_KEY_STATE_UP
#define FTGFX_MOUSE_STATE_PRESSED FTGFX_KEY_STATE_PRESSED
#define FTGFX_MOUSE_STATE_DOWN FTGFX_KEY_STATE_DOWN

/* Any shift key. */
#define FTGFX_KEYMOD_SHIFT (1 << 1)
/* Any control key. */
#define FTGFX_KEYMOD_CONTROL (1 << 2)
/* Any alt key. */
#define FTGFX_KEYMOD_ALT (1 << 3)
/* Windows key / 'command' mac key. */
#define FTGFX_KEYMOD_SUPER (1 << 4)
/* Capslock on. */
#define FTGFX_KEYMOD_CAPSLOCK (1 << 5)
/* Numlock on. */
#define FTGFX_KEYMOD_NUMLOCK (1 << 6)

struct s_ftGFX_ctx
{
	struct s_ftGFX_window *windows;

	t_time global_time;
	t_time delta_time_clk;
	F32 delta_time;

	struct s_ftGFX_window *active_window;

	U8 private[0];
};

struct s_ftGFX_window
{
	struct s_ftGFX_ctx *ctx;

	t_image *surface;

	t_iv2 size;
	string name;
	t_iv4 damage;

	bool should_close;

	S8 keys[_FTGFX_KEY_MAX];
	S8 mouse[9];
	t_iv2 mouse_delta;

	struct s_ftGFX_window *next;

	U8 private[0];
};

enum e_ftGFX_event
{
	/* Mouse down (press) event. Use `event->mouse`. */
	FTGFX_MOUSE_PRESS_EVENT,
	/* Mouse up (release) event. Use `event->mouse`. */
	FTGFX_MOUSE_RELEASE_EVENT,
	/* Mouse move event. Use `event->mouse`. */
	FTGFX_MOUSE_MOVE_EVENT,

	/* Mouse enter event. Use `event->mouse`. */
	FTGFX_MOUSE_ENTER_EVENT,
	/* Mouse leave event. Use `event->mouse`. */
	FTGFX_MOUSE_LEAVE_EVENT,

	/* Key press event. Use `event->key`. */
	FTGFX_KEY_PRESS_EVENT,
	/* Key release event. Use `event->key`. */
	FTGFX_KEY_RELEASE_EVENT,

	/* Window damage event. Use `event->damage`. */
	FTGFX_WINDOW_DAMAGE_EVENT,

	/* Focus in event. Use `event->focus`. */
	FTGFX_FOCUS_IN_EVENT,

	/* Focus in event. Use `event->focus`. */
	FTGFX_FOCUS_OUT_EVENT,

	_FTGFX_EVENT_MAX,
};

struct s_ftGFX_mouse_event
{
	t_iv2 pos;
	enum e_ftGFX_mouse_button button;
	U32 modifiers;
};

struct s_ftGFX_key_event
{
	enum e_ftGFX_key key;
	U32 modifiers;
	U32 unicode;
};

struct s_ftGFX_damage_event
{
	t_iv4 rect;
};

struct s_ftGFX_focus_event
{
};

struct s_ftGFX_event
{
	enum e_ftGFX_event type;
	struct s_ftGFX_window *window;

	union
	{
		struct s_ftGFX_mouse_event mouse;
		struct s_ftGFX_key_event key;
		struct s_ftGFX_damage_event damage;
		struct s_ftGFX_focus_event focus;
	};
};

/*
Creates a FTGR context.
### On error
Returns NULL and sets ft_errno.
### ft_errno
- FT_EOMEM if out of memory.
- FT_EINVOP if an internal error occurred.
*/
struct s_ftGFX_ctx *ftGFX_create_ctx();

/* Destroys a FTGR context and all it's associated windows. */
void ftGFX_destroy_ctx(struct s_ftGFX_ctx *ctx);

/* Begins a new frame. */
void ftGFX_new_frame(struct s_ftGFX_ctx *ctx);

/*
Waits for then polls an event. Will fill `event` with the current event data.
Returns `TRUE` if an event was processed.
*/
bool ftGFX_wait(struct s_ftGFX_ctx *ctx, struct s_ftGFX_event *event);

/*
Polls for events. Will fill `event` with the current event data.
Returns `TRUE` if an event was processed.
*/
bool ftGFX_poll(struct s_ftGFX_ctx *ctx, struct s_ftGFX_event *event);

/*
Handles all the events available. Shortcut for
```c
while (ftGFX_poll(ctx, &event))
	ftGFX_process_event(&event);
```
*/
void ftGFX_poll_all(struct s_ftGFX_ctx *ctx);

/* Processes the event internally, update stuff like `window->mouse`, `window->keys`... */
void ftGFX_process_event(struct s_ftGFX_event *event);

/*
Creates a new window.
### On error
Returns NULL and sets ft_errno.
### ft_errno
- FT_EOMEM if out of memory.
- FT_EINVOP if an internal error occurred.
*/
struct s_ftGFX_window *ftGFX_create_window(struct s_ftGFX_ctx *ctx, t_iv2 size, const_string title);

void ftGFX_destroy_window(struct s_ftGFX_window *win);
void ftGFX_bring_top(struct s_ftGFX_window *win);
void ftGFX_set_win_name(struct s_ftGFX_window *win, string name);
/* Copies the string `infos` after the window's name */
void ftGFX_set_win_name_infos(struct s_ftGFX_window *win, string infos);
void ftGFX_move_window(struct s_ftGFX_window *win, t_iv2 pos);
/* Draws the current window surface to the screen */
void ftGFX_blt_screen(struct s_ftGFX_window *win);

/*
Retrieves the current mouse position. If `win != NULL`, the position is returned relative to the window.
Otherwise, the position is in absolute screen coordinates.
*/
t_iv2 ftGFX_mouse_get_pos(struct s_ftGFX_ctx *ctx, struct s_ftGFX_window *win);

/*
Moves the mouse cursor to the specified position. If `win != NULL`, `pos` is relative to the window.
Otherwise, `pos` is treated as absolute screen coordinates.
*/
void ftGFX_mouse_set_pos(struct s_ftGFX_ctx *ctx, struct s_ftGFX_window *win, t_iv2 pos);

/* Hides the mouse cursor. */
void ftGFX_hide_mouse(struct s_ftGFX_ctx *ctx, struct s_ftGFX_window *win);

/* Shows the mouse cursor. */
void ftGFX_show_mouse(struct s_ftGFX_ctx *ctx, struct s_ftGFX_window *win);

/* Returns `TRUE` if `key` was pressed. */
inline ALWAYS_INLINE bool ftGFX_is_key_pressed(struct s_ftGFX_window *window, enum e_ftGFX_key key)
{
	if (key > FTGFX_KEY_UNKNOWN && (U64)key < statarray_len(window->keys))
		return window->keys[key] == FTGFX_KEY_STATE_PRESSED;
	return FALSE;
}

/* Returns `TRUE` if `key` is down. */
inline ALWAYS_INLINE bool ftGFX_is_key_down(struct s_ftGFX_window *window, enum e_ftGFX_key key)
{
	if (key > FTGFX_KEY_UNKNOWN && (U64)key < statarray_len(window->keys))
		return window->keys[key] == FTGFX_KEY_STATE_DOWN || ftGFX_is_key_pressed(window, key);
	return FALSE;
}

/* Returns `TRUE` if `key` was released. */
inline ALWAYS_INLINE bool ftGFX_is_key_released(struct s_ftGFX_window *window, enum e_ftGFX_key key)
{
	if (key > FTGFX_KEY_UNKNOWN && (U64)key < statarray_len(window->keys))
		return window->keys[key] == FTGFX_KEY_STATE_RELEASED;
	return FALSE;
}

/* Returns `TRUE` if `key` is up. */
inline ALWAYS_INLINE bool ftGFX_is_key_up(struct s_ftGFX_window *window, enum e_ftGFX_key key)
{
	if (key > FTGFX_KEY_UNKNOWN && (U64)key < statarray_len(window->keys))
		return window->keys[key] == FTGFX_KEY_STATE_UP || ftGFX_is_key_released(window, key);
	return FALSE;
}

/* Returns `TRUE` if `mouse` was pressed. */
inline ALWAYS_INLINE bool ftGFX_is_mouse_pressed(struct s_ftGFX_window *window, U8 mouse)
{
	if (mouse < statarray_len(window->mouse))
		return window->mouse[mouse] == FTGFX_MOUSE_STATE_PRESSED;
	return FALSE;
}

/* Returns `TRUE` if `mouse` is down. */
inline ALWAYS_INLINE bool ftGFX_is_mouse_down(struct s_ftGFX_window *window, U8 mouse)
{
	if (mouse < statarray_len(window->mouse))
		return window->mouse[mouse] == FTGFX_MOUSE_STATE_DOWN || ftGFX_is_mouse_pressed(window, mouse);
	return FALSE;
}

/* Returns `TRUE` if `mouse` was released. */
inline ALWAYS_INLINE bool ftGFX_is_mouse_released(struct s_ftGFX_window *window, U8 mouse)
{
	if (mouse < statarray_len(window->mouse))
		return window->mouse[mouse] == FTGFX_MOUSE_STATE_RELEASED;
	return FALSE;
}

/* Returns `TRUE` if `mouse` is up. */
inline ALWAYS_INLINE bool ftGFX_is_mouse_up(struct s_ftGFX_window *window, U8 mouse)
{
	if (mouse < statarray_len(window->mouse))
		return window->mouse[mouse] == FTGFX_MOUSE_STATE_UP || ftGFX_is_mouse_released(window, mouse);
	return FALSE;
}

void ftGFX_key_autorepeat(struct s_ftGFX_ctx *ctx, bool active);

/* Returns the time since application start */
float ftGFX_time(struct s_ftGFX_ctx *ctx);

/* Returns the time elapsed for last frame */
float ftGFX_delta_time(struct s_ftGFX_ctx *ctx);

/* Displays the FPS in the window's info */
void ftGFX_display_fps(struct s_ftGFX_window *win);

/* Sets the current cursor to `cursor`. Uses the system's cursor. */
void ftGFX_cursor_set(struct s_ftGFX_window *win, enum e_ftGFX_cursor cursor);

/*
void		ftGFX_clear_window(t_ftGFX_ctx *xvar, t_ftGFX_win *win);

t_iv2		ftGFX_get_screen_size(t_ftGFX_ctx *ctx);
*/

#endif

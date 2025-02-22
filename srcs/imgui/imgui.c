/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:38:28 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/14 03:07:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#define USE_FT_PRINTF 0

#include "libftgr.h"

#include "./bitmap-baked.h"

#include "libft/crypt/crc.h"
#include "libft/io.h"
#include "libft/limits.h"
#include "libft/macros.h"
#include "libft/maths.h"
#include "libft/strings.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define EXP(...)			   __VA_ARGS__
#define _CONCAT(x, y)		   x##y
#define CONCAT(x, y)		   EXP(_CONCAT(x, y))
#define STACK_NAME(type)	   stack_##type
#define STACK(type)			   struct CONCAT(s_, STACK_NAME(type))
#define STACK_FUNC(type, func) CONCAT(STACK_NAME(type), _##func)
#define DEFINE_STACK(type)                                                                         \
	STACK(type)                                                                                    \
	{                                                                                              \
		U64	  stack_n;                                                                             \
		U64	  stack_alloc;                                                                         \
		type *elems;                                                                               \
	};                                                                                             \
                                                                                                   \
	void STACK_FUNC(type, init)(STACK(type) * st)                                                  \
	{                                                                                              \
		st->stack_alloc = 8;                                                                       \
		if (UNLIKELY((st->elems = malloc(sizeof(type) * st->stack_alloc)) == NULL))                \
		{                                                                                          \
			ft_fprintf(ft_fstderr, "%s: out of memory\n", ft_argv[0]);                             \
			exit(2);                                                                               \
		}                                                                                          \
		st->stack_n = 0;                                                                           \
	}                                                                                              \
                                                                                                   \
	void STACK_FUNC(type, destroy)(STACK(type) * st) { free((st)->elems); }                        \
                                                                                                   \
	type *STACK_FUNC(type, push)(STACK(type) * st, type value)                                     \
	{                                                                                              \
		type *new;                                                                                 \
                                                                                                   \
		if (st->stack_n >= st->stack_alloc)                                                        \
		{                                                                                          \
			if (UNLIKELY((new = malloc(sizeof(type) * st->stack_alloc * 2)) == NULL))              \
			{                                                                                      \
				ft_fprintf(ft_fstderr, "%s: out of memory\n", ft_argv[0]);                         \
				exit(2);                                                                           \
			}                                                                                      \
			ft_memcpy(new, st->elems, sizeof(type) * st->stack_n);                                 \
			free(st->elems);                                                                       \
			st->elems = new;                                                                       \
			st->stack_alloc *= 2;                                                                  \
		}                                                                                          \
		new = &st->elems[st->stack_n];                                                             \
		*new = value;                                                                              \
		st->stack_n++;                                                                             \
		return new;                                                                                \
	}                                                                                              \
                                                                                                   \
	type *STACK_FUNC(type, top)(STACK(type) * st)                                                  \
	{                                                                                              \
		if (st->stack_n == 0)                                                                      \
			return NULL;                                                                           \
		return &st->elems[st->stack_n - 1];                                                        \
	}                                                                                              \
                                                                                                   \
	type *STACK_FUNC(type, pop)(STACK(type) * st)                                                  \
	{                                                                                              \
		type *elem;                                                                                \
                                                                                                   \
		if (st->stack_n == 0)                                                                      \
			return NULL;                                                                           \
		elem = &st->elems[st->stack_n - 1];                                                        \
		st->stack_n--;                                                                             \
		return elem;                                                                               \
	}

#define STACK_INIT(type, st)	  STACK_FUNC(type, init)((st))
#define STACK_DESTROY(type, st)	  STACK_FUNC(type, destroy)((st))
#define STACK_PUSH(type, st, val) STACK_FUNC(type, push)((st), (val))
#define STACK_TOP(type, st)		  STACK_FUNC(type, top)((st))
#define STACK_POP(type, st)		  STACK_FUNC(type, pop)((st))

DEFINE_STACK(t_color);
DEFINE_STACK(S32);

typedef void (*f_draw_command)(t_image *img);

enum e_cmd_type
{
	CMD_BEGIN_FRAME,
	CMD_END_FRAME,

	CMD_TEXT,

	CMD_IMAGE,

	CMD_BUTTON,
	CMD_CHECKBOX,
	CMD_SLIDER,

	CMD_WINDOW,
	CMD_FRAME,

	CMD_STYLE_COLOR_PUSH,
	CMD_STYLE_COLOR_POP,
};

struct s_draw_command
{
	enum e_cmd_type type;

	union
	{
		struct
		{
			string str;
			t_iv4  rect;
		} text;

		struct
		{
			t_image *img;
			t_iv4  rect;
		} img;

		struct
		{
			string str;
			t_iv4  rect;
			bool   clicked;
			bool   hovered;
		} button;

		struct
		{
			string str;
			t_iv4  rect;
			bool   clicked;
			bool   hovered;
			F64	   v;
		} slider;

		struct
		{
			string str;
			t_iv4  rect;
			bool   clicked;
			bool   hovered;
			bool   on;
		} checkbox;

		struct
		{
			t_color col;
			t_iv4	rect;
		} frame;

		t_color style_push_color;
	};
};

typedef struct s_drawing_context
{
	struct
	{
		t_iv2 pos;
	} layout;

	struct
	{
		t_bitmap text_bitmap;
		F32		 text_scale;
		t_iv2	 text_kerning;

		t_iv4	 button_shadow_ofs;
		t_iv4	 button_text_margins;

		t_iv4	 checkbox_text_margins;

		t_iv4	 slider_text_margins;
		U32		 slider_width;

		t_iv4	 frame_margins;

		S32		 y_spacing;
	} params;

	STACK(t_color) color_style_stack;
	STACK(S32) indent_style_stack;

	t_iv4 dc_rect;
} t_dc;

DEFINE_STACK(t_dc);

struct s_debugui
{
	t_iv2				   mouse_pos;
	bool				   clicked[3];

	U64					   draw_commands_n;
	U64					   draw_commands_alloc;
	struct s_draw_command *draw_commands;

	U64					   hot_widget;
	U64					   active_widget;

	S32					   keyentered;
	S32					   keymod;
	S32					   keychar;

	STACK(t_dc) drawing_context_stack;
	t_dc root_dc;
};

struct s_debugui *debugui;

/*
returns the unique id associated with the string `*str`.
Always duplicates `*str`, and puts the new string at the address pointer to by `str`
If any '##' is found in `str`, cuts it off in newly allocated string before returning */
static U64 get_widget_id(string *str);

/* check if the mouse is in the specified rectangle `rect`, using the cached mouse_pos in `debugui`
 */
static bool mouse_in(t_iv4 rect);
/* check if a widget (identified by `id`) is hovered or clicked, and update states in `debugui` */
static void update_interactable_widget(U64 id, t_iv4 rect, bool *hovered, bool *clicked,
									   bool *clicked_this_frame);

/* returns the current color, depending on what is set in the `color_style_stack` in `debugui` */
static t_color get_current_color();

/* initializes a new DC (allocates memory) */
static void dc_init(t_dc *dc);
/* destroys a DC */
static void dc_destroy(t_dc *dc);
/* sets the drawing context `dc` to default values */
static void dc_init_defaults(t_dc *dc);
/* pushes a new drawing context, and initializes it. Returns the new DC */
static t_dc *dc_push();
/*
pops the current drawing context, and updates the previous one according. Returns the popped DC.
/!\ The returned DC must is not destroyed, and must be destroyed when done (`dc_destroy()`)
*/
static t_dc *dc_pop();
/* returns the current drawing position in a drawing context (in a t_iv4 for convenience) */
static t_iv4 dc_get_current_pos(t_dc *dc);
/* computes the next drawing position */
static void dc_advance(t_dc *dc, t_iv4 rect);
/* computes the next drawing position */
static void dc_advance_x(t_dc *dc, S32 new_x);
/* returns the current drawing context. Returns `&debugui->root_dc` if no DC are active */
inline static t_dc *get_current_dc();

/*
calls `ft_vsaprintf(fmt, lst)`, stores the resulting string's rectangle that is required for it to
be drawn (according the parameters specified in `dc`) in `out_rect`, and returns the resulting
string
*/
static string do_format_text(t_dc *dc, t_iv4 *out_rect, const_string fmt, va_list lst);
/* calls `ftgr_draw_bitmap_text`, using rect `rect` and the the parameters specified in `debugui` */
static void display_text(t_image *img, t_dc *dc, string text, t_iv4 rect);

/*
computes the different rectangles that make up a button:
	- original_text_rect: the rect returned by `do_format_text`.
	- text_rect: the newly computed text rect
	- button_rect: the rect of the button
	- shadow_rect: the rect of the button's shadow
	- rect: the total space taken by the button
*/
static void compute_button_rects(t_dc *dc, t_iv4 original_text_rect, t_iv4 *text_rect,
								 t_iv4 *button_rect, t_iv4 *shadow_rect, t_iv4 *rect);

/*
computes the different rectangles that make up a checkbox:
	- original_text_rect: the rect returned by `do_format_text`.
	- text_rect: the newly computed text rect
	- checkbox_rect: the rect of the checkbox
	- rect: the total space taken by the checkbox
*/
static void compute_checkbox_rects(t_dc *dc, t_iv4 original_text_rect, t_iv4 *text_rect,
								   t_iv4 *checkbox_rect, t_iv4 *rect);

/* allocates space for and returns a new draw command */
static struct s_draw_command *new_draw_command();

static bool mouse_in(t_iv4 rect)
{
	t_iv2 mp;

	mp = debugui->mouse_pos;

	if (mp.x >= rect.x && mp.x < rect.z && mp.y >= rect.y && mp.y < rect.w)
		return TRUE;
	return FALSE;
}

static void update_interactable_widget(U64 id, t_iv4 rect, bool *hovered, bool *clicked,
									   bool *clicked_this_frame)
{
	*clicked_this_frame = FALSE;
	if (mouse_in(rect))
	{
		debugui->hot_widget = id;
		if (debugui->active_widget == 0 && debugui->clicked[0])
		{
			debugui->active_widget = id;
			*clicked_this_frame = TRUE;
		}
	}

	if (debugui->hot_widget == id)
	{
		*hovered = TRUE;
		if (debugui->active_widget == id)
			*clicked = TRUE;
		else
			*clicked = FALSE;
	}
	else
	{
		*hovered = FALSE;
		*clicked = FALSE;
	}
}

static t_color get_current_color()
{
	t_dc *dc;

	dc = get_current_dc();
	if (dc->color_style_stack.stack_n != 0)
		return *STACK_TOP(t_color, &dc->color_style_stack);
	return ftgr_color(255, 255, 255, 255);
}

static void dc_init(t_dc *dc)
{
	STACK_INIT(t_color, &dc->color_style_stack);
	STACK_INIT(S32, &dc->indent_style_stack);

	STACK_PUSH(t_color, &dc->color_style_stack, ftgr_color(255, 255, 255, 255));
}

static void dc_destroy(t_dc *dc)
{
	STACK_DESTROY(t_color, &dc->color_style_stack);
	STACK_DESTROY(S32, &dc->indent_style_stack);
}

static void dc_init_defaults(t_dc *dc)
{
	dc->layout.pos = ivec2(10, 10);

	// TODO: plus tard faudra push/pull les bitmaps a utiliser
	// dc->params.text_bitmap
	dc->params.text_kerning = ivec2(2, 2);
	dc->params.text_scale = 2.0f;
	dc->params.y_spacing = 5;

	dc->color_style_stack.stack_n = 1;
	dc->indent_style_stack.stack_n = 0;

	dc->params.button_shadow_ofs = ivec4(3, 3, 3, 3);
	dc->params.button_text_margins = ivec4(4, 4, 5, 5);

	dc->params.checkbox_text_margins = ivec4(10, 1, 0, 1);

	dc->params.slider_text_margins = ivec4(10, 1, 0, 1);
	dc->params.slider_width = 100;

	dc->params.frame_margins = ivec4(10, 10, 10, 10);

	dc->dc_rect = ivec4(dc->layout.pos.x, dc->layout.pos.y, dc->layout.pos.x, dc->layout.pos.y);
}

static t_dc *dc_push()
{
	t_dc *old_dc;
	t_dc *dc;

	old_dc = STACK_TOP(t_dc, &debugui->drawing_context_stack);
	dc = STACK_PUSH(t_dc, &debugui->drawing_context_stack, (t_dc) {0});

	dc_init(dc);
	dc_init_defaults(dc);
	dc->layout.pos = old_dc->layout.pos;
	dc->dc_rect = ivec4(old_dc->layout.pos.x, old_dc->layout.pos.y, old_dc->layout.pos.x,
						old_dc->layout.pos.y);
	dc->params.text_bitmap = old_dc->params.text_bitmap;
	dc->params.text_kerning = old_dc->params.text_kerning;
	dc->params.text_scale = old_dc->params.text_scale;

	dc->params.y_spacing = old_dc->params.y_spacing;
	return dc;
}

static t_dc *dc_pop()
{
	t_dc *old_dc;

	if (debugui->drawing_context_stack.stack_n <= 1)
		return STACK_TOP(t_dc, &debugui->drawing_context_stack);

	old_dc = STACK_POP(t_dc, &debugui->drawing_context_stack);

	return old_dc;
}

inline static t_dc *get_current_dc() { return STACK_TOP(t_dc, &debugui->drawing_context_stack); }

static t_iv4 dc_get_current_pos(t_dc *dc)
{
	t_iv4 rect;

	// TODO: columns
	rect.x = dc->layout.pos.x;
	rect.y = dc->layout.pos.y;

	for (U64 i = 0; i < dc->indent_style_stack.stack_n; i++)
		rect.x += dc->indent_style_stack.elems[i];

	rect.z = rect.x;
	rect.w = rect.y;

	return rect;
}

static void dc_advance(t_dc *dc, t_iv4 rect)
{
	// TODO: columns
	dc->layout.pos.y = rect.w + dc->params.y_spacing;

	dc->dc_rect.x = ft_imin(rect.x, dc->dc_rect.x);
	dc->dc_rect.y = ft_imin(rect.y, dc->dc_rect.y);
	dc->dc_rect.z = ft_imax(rect.z, dc->dc_rect.z);
	dc->dc_rect.w = ft_imax(rect.w, dc->dc_rect.w);
}

static void dc_advance_x(t_dc *dc, S32 new_x)
{
	// TODO: columns
	dc->layout.pos.x = new_x;

	/*
		dc_get_current_pos(&rect);
		dc->dc_rect.x = ft_imin(rect.x, dc->dc_rect.x);
		dc->dc_rect.y = ft_imin(rect.y, dc->dc_rect.y);
		dc->dc_rect.z = ft_imax(rect.z, dc->dc_rect.z);
		dc->dc_rect.w = ft_imax(rect.w, dc->dc_rect.w);
	*/
}

static string do_format_text(t_dc *dc, t_iv4 *out_rect, const_string fmt, va_list lst)
{
	string str;
	U64	   len;
	U64	   char_size;
	U64	   line_size;
	t_iv4  rect;

#if USE_FT_PRINTF
	if (UNLIKELY((str = ft_vsaprintf(fmt, lst)) == NULL))
	{
		ft_fprintf(ft_fstderr, "%s: out of memory\n", ft_argv[0]);
		exit(2);
	}
	len = ft_strlen(str);
#else
	len = vasprintf(&str, fmt, lst);
#endif

	char_size
		= (dc->params.text_bitmap.char_width * dc->params.text_scale + dc->params.text_kerning.x);
	line_size
		= (dc->params.text_bitmap.char_height * dc->params.text_scale + dc->params.text_kerning.y);

	rect = dc_get_current_pos(dc);
	rect.z += (char_size * len) - dc->params.text_kerning.x;
	rect.w += line_size - dc->params.text_kerning.y;

	*out_rect = rect;
	return str;
}

static void display_text(t_image *img, t_dc *dc, string str, t_iv4 rect)
{
	ftgr_draw_bitmap_text(img, rect, &dc->params.text_bitmap, str, dc->params.text_scale,
						  dc->params.text_kerning, get_current_color());
}

static void compute_button_rects(t_dc *dc, t_iv4 original_text_rect, t_iv4 *text_rect,
								 t_iv4 *button_rect, t_iv4 *shadow_rect, t_iv4 *rect)
{
	*text_rect = original_text_rect;
	text_rect->x += dc->params.button_text_margins.x;
	text_rect->y += dc->params.button_text_margins.y;
	text_rect->z += dc->params.button_text_margins.x;
	text_rect->w += dc->params.button_text_margins.y;

	*button_rect = original_text_rect;
	button_rect->z += dc->params.button_text_margins.x + dc->params.button_text_margins.z;
	button_rect->w += dc->params.button_text_margins.y + dc->params.button_text_margins.w;

	*shadow_rect = ivec4_add(*button_rect, dc->params.button_shadow_ofs);

	rect->x = button_rect->x;
	rect->y = button_rect->y;
	rect->z = shadow_rect->z;
	rect->w = shadow_rect->w;
}

static void compute_checkbox_rects(t_dc *dc, t_iv4 original_text_rect, t_iv4 *text_rect,
								   t_iv4 *checkbox_rect, t_iv4 *rect)
{
	S32 chekbox_height;

	// Checkbox size basé sur la hauteur du texte seulement
	chekbox_height = original_text_rect.w - original_text_rect.y;
	checkbox_rect->x = original_text_rect.x;
	checkbox_rect->y = original_text_rect.y + dc->params.checkbox_text_margins.y;
	checkbox_rect->z = original_text_rect.x + chekbox_height;
	checkbox_rect->w = original_text_rect.y + chekbox_height;

	*text_rect = original_text_rect;
	text_rect->x += dc->params.checkbox_text_margins.x + checkbox_rect->w;
	text_rect->y += dc->params.checkbox_text_margins.y;
	text_rect->z += dc->params.checkbox_text_margins.x + checkbox_rect->w;
	text_rect->w += dc->params.checkbox_text_margins.y;

	rect->x = original_text_rect.x;
	rect->y = original_text_rect.y;
	rect->z = text_rect->z + dc->params.checkbox_text_margins.z;
	rect->w = text_rect->w + dc->params.checkbox_text_margins.w;
}

static void compute_slider_rects(t_dc *dc, t_iv4 original_text_rect, t_iv4 *text_rect,
								 t_iv4 *slider_rect, t_iv4 *rect)
{
	S32 slider_height;

	slider_height = original_text_rect.w - original_text_rect.y;
	slider_rect->x = original_text_rect.x;
	slider_rect->y = original_text_rect.y + dc->params.slider_text_margins.y;
	slider_rect->z = original_text_rect.x + dc->params.slider_width;
	slider_rect->w = original_text_rect.y + dc->params.slider_text_margins.y + slider_height;

	*text_rect = original_text_rect;
	text_rect->x += dc->params.slider_text_margins.x + slider_rect->w;
	text_rect->y += dc->params.slider_text_margins.y;
	text_rect->z += dc->params.slider_text_margins.x + slider_rect->w;
	text_rect->w += dc->params.slider_text_margins.y;

	rect->x = original_text_rect.x;
	rect->y = original_text_rect.y;
	rect->z = text_rect->z + dc->params.slider_text_margins.z;
	rect->w = text_rect->w + dc->params.slider_text_margins.w;
}

MAYBE_UNUSED
static t_iv4 compute_slider_thumb_rect(t_dc *dc, t_iv4 slider_rect, F64 val)
{
	t_iv4 rect;
	U32	  thumb_margin;

	thumb_margin = (slider_rect.w - slider_rect.y) * 0.1f;
	rect.x = slider_rect.x + thumb_margin;
	rect.y = slider_rect.y + thumb_margin;
	rect.z = slider_rect.x - thumb_margin + 10;
	rect.w = slider_rect.w - thumb_margin;

	rect.x += dc->params.slider_width * val;
	rect.z += dc->params.slider_width * val;

	return rect;
}

static struct s_draw_command *new_draw_command()
{
	struct s_draw_command *new;

	if (debugui->draw_commands_n >= debugui->draw_commands_alloc)
	{
		if (UNLIKELY(
				(new = malloc(sizeof(struct s_draw_command) * debugui->draw_commands_alloc * 2))
				== NULL))
			return NULL;
		ft_memcpy(new, debugui->draw_commands,
				  sizeof(struct s_draw_command) * debugui->draw_commands_n);
		free(debugui->draw_commands);
		debugui->draw_commands = new;
		debugui->draw_commands_alloc *= 2;
	}
	return &debugui->draw_commands[debugui->draw_commands_n++];
}

static U64 get_widget_id(string *str)
{
	string newstr;
	string to_remove;
	U64	   hash;
	U64	   len;

	len = ft_strlen(*str);
	hash = ft_crc32((U8 *) (*str), len);

	if (UNLIKELY((newstr = ft_strdup(*str)) == NULL))
	{
		ft_fprintf(ft_fstderr, "%s: out of memory\n", ft_argv[0]);
		exit(2);
	}

	if ((to_remove = (string) ft_strnstr(newstr, "##", len)))
		*to_remove = '\0';

	*str = newstr;
	return hash;
}

__attribute__((constructor)) static void init()
{
	t_dc *root_dc;

	if (UNLIKELY((debugui = malloc(sizeof(struct s_debugui))) == NULL))
	{
		ft_fprintf(ft_fstderr, "%s: out of memory\n", ft_argv[0]);
		exit(2);
	}

	debugui->clicked[0] = FALSE;
	debugui->clicked[1] = FALSE;
	debugui->clicked[2] = FALSE;

	debugui->active_widget = 0;
	debugui->hot_widget = 0;

	debugui->draw_commands_n = 0;
	debugui->draw_commands_alloc = 32;
	if (UNLIKELY((debugui->draw_commands
				  = malloc(sizeof(struct s_draw_command) * debugui->draw_commands_alloc))
				 == NULL))
	{
		ft_fprintf(ft_fstderr, "%s: out of memory\n", ft_argv[0]);
		exit(2);
	}

	STACK_INIT(t_dc, &debugui->drawing_context_stack);
	debugui->drawing_context_stack.stack_n = 1;
	root_dc = &debugui->drawing_context_stack.elems[0];

	dc_init(root_dc);
	dc_init_defaults(root_dc);
	ftgr_init_bitmap(&root_dc->params.text_bitmap, baked_bitmap, ivec2(5, 7), 18,
					 ivec2(2, 2));
}

__attribute__((destructor)) static void destroy()
{
	dc_destroy(&debugui->drawing_context_stack.elems[0]);
	STACK_DESTROY(t_dc, &debugui->drawing_context_stack);
	free(debugui->draw_commands);
	free(debugui);
}

/* === PUBLIC INTERFACE === */

void DBGUI_events(t_ftgr_ctx *ctx)
{
	debugui->clicked[MOUSE_LEFT] = ftgr_mouse_pressed(ctx, MOUSE_LEFT);
	debugui->clicked[MOUSE_MIDDLE] = ftgr_mouse_pressed(ctx, MOUSE_MIDDLE);
	debugui->clicked[MOUSE_RIGHT] = ftgr_mouse_pressed(ctx, MOUSE_RIGHT);
}

/*
void DBGUI_key_hook(mlx_key_data_t key)
{
	if (key.key > 255 || !ft_isprint(key.key))
		return;

	if (!(key.modifier & MLX_SHIFT))
		key.key += 32;
	debugui->keychar = key.key;
}
*/

void DBGUI_begin(t_iv2 mouse_pos)
{
	debugui->mouse_pos = mouse_pos;

	debugui->draw_commands_n = 0;

	debugui->drawing_context_stack.stack_n = 1;
	dc_init_defaults(&debugui->drawing_context_stack.elems[0]);
	get_current_dc()->layout.pos = ivec2(10, 10);

	debugui->hot_widget = 0;
}

void DBGUI_style_color_push(t_color col)
{
	struct s_draw_command *cmd;

	cmd = new_draw_command();
	cmd->type = CMD_STYLE_COLOR_PUSH;
	cmd->style_push_color = col;
}

void DBGUI_style_color_pop()
{
	struct s_draw_command *cmd;

	cmd = new_draw_command();
	cmd->type = CMD_STYLE_COLOR_POP;
}

void DBGUI_style_indent_push(S32 indent)
{
	t_dc *dc;

	dc = get_current_dc();
	STACK_PUSH(S32, &dc->indent_style_stack, indent);
}

void DBGUI_style_indent_pop()
{
	t_dc *dc;

	dc = get_current_dc();
	STACK_POP(S32, &dc->indent_style_stack);
}

void DBGUI_style_vert_space(S32 size)
{
	t_dc *dc;
	t_iv4 rect;

	dc = get_current_dc();
	rect = dc_get_current_pos(dc);
	rect.w += size;
	dc_advance(dc, rect);
}

void DBGUI_begin_frame(t_color col)
{
	struct s_draw_command *cmd;
	t_iv4				   rect;
	t_dc				  *dc;

	cmd = new_draw_command();
	cmd->type = CMD_BEGIN_FRAME;

	cmd->frame.col = col;
	dc = dc_push();

	rect = dc_get_current_pos(dc);
	rect.w += dc->params.frame_margins.y;
	dc_advance(dc, rect);
	dc_advance_x(dc, dc->layout.pos.x + 10);
}

void DBGUI_end_frame()
{
	struct s_draw_command *cmd;
	struct s_draw_command *begin_frame_cmd;
	S32					   depth;
	t_iv4				   rect;
	t_dc				  *dc;

	cmd = new_draw_command();
	cmd->type = CMD_END_FRAME;

	begin_frame_cmd = NULL;
	if (debugui->draw_commands_n >= 2)
	{
		depth = 0;
		for (U64 i = debugui->draw_commands_n - 2; i > 0; i--)
		{
			if (debugui->draw_commands[i].type == CMD_END_FRAME)
				depth++;
			else if (debugui->draw_commands[i].type == CMD_BEGIN_FRAME)
			{
				if (depth == 0)
				{
					begin_frame_cmd = &debugui->draw_commands[i];
					break;
				}
				else
					depth--;
			}
		}
		if (debugui->draw_commands[0].type == CMD_BEGIN_FRAME)
			begin_frame_cmd = &debugui->draw_commands[0];
	}

	if (begin_frame_cmd == NULL)
	{
		ft_fprintf(ft_fstderr, "%s: warning: no end frame found\n", ft_argv[0]);
		return;
	}

	dc = dc_pop();

	rect = dc->dc_rect;
	rect.z += dc->params.frame_margins.z;
	rect.w += dc->params.frame_margins.w;
	dc_advance(get_current_dc(), rect);

	begin_frame_cmd->frame.rect = rect;
	dc_destroy(dc);

	DBGUI_style_indent_pop();

	// dc_pop calls dc_advance
}

void DBGUI_text(const_string fmt, ...)
{
	struct s_draw_command *cmd;
	t_dc				  *dc;
	va_list				   lst;

	dc = get_current_dc();
	cmd = new_draw_command();
	cmd->type = CMD_TEXT;

	va_start(lst, fmt);
	cmd->text.str = do_format_text(dc, &cmd->text.rect, fmt, lst);
	va_end(lst);

	dc_advance(dc, cmd->text.rect);
}

void DBGUI_img(t_image *img)
{
	struct s_draw_command *cmd;
	t_dc				  *dc;
	t_iv4				   rect;

	dc = get_current_dc();
	img = baked_bitmap;
	rect = dc_get_current_pos(dc);

	rect.z += img->size.x;
	rect.w += img->size.y;

	cmd = new_draw_command();
	cmd->type = CMD_IMAGE;
	cmd->img.img = img;
	cmd->img.rect = rect;

	dc_advance(dc, rect);
}

bool DBGUI_button(string fmt, ...)
{
	t_dc				  *dc;
	struct s_draw_command *cmd;

	bool				   clicked_this_frame;

	U64					   id;
	t_iv4				   rect;
	t_iv4				   dummy1, dummy2, dummy3;

	va_list				   lst;
	string				   str;
	t_iv4				   text_rect;

	dc = get_current_dc();
	cmd = new_draw_command();
	cmd->type = CMD_BUTTON;

	id = get_widget_id(&fmt);
	va_start(lst, fmt);
	str = do_format_text(dc, &text_rect, fmt, lst);
	va_end(lst);
	free(fmt);

	cmd->button.rect = text_rect;
	cmd->button.str = str;

	compute_button_rects(dc, text_rect, &dummy1, &dummy2, &dummy3, &rect);
	update_interactable_widget(id, rect, &cmd->button.hovered, &cmd->button.clicked,
							   &clicked_this_frame);

	dc_advance(dc, rect);

	return clicked_this_frame;
}

bool DBGUI_checkbox(bool *on, string fmt, ...)
{
	t_dc				  *dc;
	struct s_draw_command *cmd;

	bool				   clicked_this_frame;

	U64					   id;
	t_iv4				   rect;
	t_iv4				   dummy1;
	t_iv4				   checkbox_rect;

	va_list				   lst;
	string				   str;
	t_iv4				   text_rect;

	dc = get_current_dc();
	cmd = new_draw_command();
	cmd->type = CMD_CHECKBOX;

	id = get_widget_id(&fmt);
	va_start(lst, fmt);
	str = do_format_text(dc, &text_rect, fmt, lst);
	va_end(lst);
	free(fmt);

	cmd->checkbox.rect = text_rect;
	cmd->checkbox.str = str;

	compute_checkbox_rects(dc, text_rect, &dummy1, &checkbox_rect, &rect);
	update_interactable_widget(id, checkbox_rect, &cmd->checkbox.hovered, &cmd->checkbox.clicked,
							   &clicked_this_frame);
	dc_advance(dc, rect);

	if (clicked_this_frame)
		*on = !(*on);
	cmd->checkbox.on = *on;
	return clicked_this_frame;
}

bool DBGUI_slider(F64 *value, F64 min, F64 max, string fmt, ...)
{
	t_dc				  *dc;
	struct s_draw_command *cmd;

	bool				   clicked_this_frame;

	U64					   id;
	t_iv4				   rect;
	t_iv4				   dummy1;
	t_iv4				   slider_rect;

	va_list				   lst;
	string				   str;
	t_iv4				   text_rect;

	(void) min;
	(void) max;
	(void) value;

	dc = get_current_dc();
	cmd = new_draw_command();
	cmd->type = CMD_SLIDER;

	id = get_widget_id(&fmt);
	va_start(lst, fmt);
	str = do_format_text(dc, &text_rect, fmt, lst);
	va_end(lst);
	free(fmt);

	cmd->slider.rect = text_rect;
	cmd->slider.str = str;

	compute_slider_rects(dc, text_rect, &dummy1, &slider_rect, &rect);
	update_interactable_widget(id, slider_rect, &cmd->slider.hovered, &cmd->slider.clicked,
							   &clicked_this_frame);
	dc_advance(dc, rect);

	if (debugui->active_widget == id)
	{
		cmd->slider.v = ((F64) (debugui->mouse_pos.x - slider_rect.x)
						 / (F64) (slider_rect.z - slider_rect.x));
		*value = ft_map(cmd->slider.v, vec2(0, 1), vec2(min, max));
	}

	return clicked_this_frame;
}

void DBGUI_render(t_image *img)
{
	struct s_draw_command *cmd;
	t_dc				  *dc;

	union
	{
		struct s_btn_vrs
		{
			t_iv4 button_text_rect;
			t_iv4 button_rect;
			t_iv4 button_shadow_rect;
			t_iv4 dummy;
		} btn;

		struct s_chk_vrs
		{
			t_iv4 checkbox_text_rect;
			t_iv4 checkbox_rect;
			t_iv4 dummy;
		} chk;

		struct s_sld_vrs
		{
			t_iv4 slider_text_rect;
			t_iv4 slider_rect;
			t_iv4 thumb_rect;
			t_iv4 dummy;
		} sld;
	} vrs;

	struct s_btn_vrs btn;
	struct s_chk_vrs chk;
	struct s_sld_vrs sld;

	dc = get_current_dc();

	for (U64 i = 0; i < debugui->draw_commands_n; i++)
	{
		cmd = &debugui->draw_commands[i];
		switch (cmd->type)
		{
		case CMD_BEGIN_FRAME:
			ftgr_fill_rect2(img, cmd->frame.rect, cmd->frame.col);
			break;

		case CMD_END_FRAME:
			break;

		case CMD_TEXT:
			display_text(img, dc, cmd->text.str, cmd->text.rect);
			free(cmd->text.str);
			break;

		case CMD_IMAGE:
			ftgr_stretch_img2(img, cmd->img.rect, cmd->img.img,
							 ivec4(0, 0, cmd->img.img->size.x, cmd->img.img->size.y),
							 get_current_color());
			break;

		case CMD_BUTTON:
			btn = vrs.btn;
			compute_button_rects(dc, cmd->button.rect, &btn.button_text_rect, &btn.button_rect,
								 &btn.button_shadow_rect, &btn.dummy);
			if (cmd->button.clicked)
				ftgr_fill_rect(img, btn.button_shadow_rect, ftgr_color(100, 100, 100, 255));
			else
			{
				ftgr_fill_rect(img, btn.button_shadow_rect, ftgr_color(50, 50, 50, 255));
				if (cmd->button.hovered)
					ftgr_fill_rect(img, btn.button_rect, ftgr_color(100, 100, 100, 255));
				else
					ftgr_fill_rect(img, btn.button_rect, ftgr_color(150, 150, 150, 255));
			}

			display_text(img, dc, cmd->button.str,
						 cmd->button.clicked
							 ? ivec4_add(btn.button_text_rect, dc->params.button_shadow_ofs)
							 : btn.button_text_rect);
			free(cmd->button.str);
			break;

		case CMD_CHECKBOX:
			chk = vrs.chk;
			compute_checkbox_rects(dc, cmd->checkbox.rect, &chk.checkbox_text_rect,
								   &chk.checkbox_rect, &chk.dummy);
			if (cmd->checkbox.clicked)
				ftgr_fill_rect2(img, chk.checkbox_rect, ftgr_color(100, 100, 100, 255));
			else
			{
				if (cmd->button.hovered)
					ftgr_fill_rect2(img, chk.checkbox_rect, ftgr_color(100, 100, 100, 255));
				else
					ftgr_fill_rect2(img, chk.checkbox_rect, ftgr_color(150, 150, 150, 255));
			}

			if (cmd->checkbox.on)
				ftgr_fill_rect2(img, ivec4_add(chk.checkbox_rect, ivec4(2, 2, -2, -2)),
								ftgr_color(255, 255, 255, 255));

			display_text(img, dc, cmd->checkbox.str, chk.checkbox_text_rect);
			free(cmd->checkbox.str);
			break;

		case CMD_SLIDER:
			sld = vrs.sld;
			compute_slider_rects(dc, cmd->slider.rect, &sld.slider_text_rect, &sld.slider_rect,
								 &sld.dummy);
			sld.thumb_rect = compute_slider_thumb_rect(dc, sld.slider_rect, cmd->slider.v);
			ftgr_fill_rect2(img, sld.slider_rect, ftgr_color(255, 255, 255, 255));
			ftgr_fill_rect2(img, sld.thumb_rect, ftgr_color(0, 0, 0, 255));
			display_text(img, dc, cmd->slider.str, sld.slider_text_rect);
			free(cmd->slider.str);
			break;

		case CMD_STYLE_COLOR_PUSH:
			STACK_PUSH(t_color, &dc->color_style_stack, cmd->style_push_color);
			break;

		case CMD_STYLE_COLOR_POP:
			STACK_POP(t_color, &dc->color_style_stack);
			break;

		default:
			break;
		}
	}

	if (!debugui->clicked[0])
		debugui->active_widget = 0;
	else if (debugui->active_widget == 0)
		debugui->active_widget = U64_MAX;

	debugui->keychar = 0;
}

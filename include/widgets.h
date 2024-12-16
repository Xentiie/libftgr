/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:02:40 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/12 12:09:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(WIDGETS_H) && !defined(WIDGETS2_H)
#define WIDGETS_H

#include "libftgr.h"

/* 32 bytes of user-data for a t_widget */
union u_widget_data
{
	U8 u8[32];
	U16 u16[16];
	U32 u32[8];
	U64 u64[4];

	F32 f32[8];
	F64 f64[4];

	t_iv2 iv2[4];
	t_iv3 iv3[2];
	t_iv4 iv4[2];

	void *ptr[4];

	t_ftgr_img *img[4];
	t_color color[8];
};

/*
`out`: target image
`widget`: target widget
`rect`: request rect to be redrawn (`ivec4(0, 0, out->size.x, out->size.y)` if drawing call is ftgr_draw_widget)
`data`: drawer data
*/
typedef void(t_widget_drawer_draw_f)(t_ftgr_img *out, t_widget *widget, t_iv4 rect, union u_widget_data data);
typedef struct s_widget_drawer
{
	t_widget_drawer_draw_f *draw_f;
	union u_widget_data data;
} t_widget_drawer;

struct s_widget_event_infos
{
	t_iv2 cursor_pos;
	t_iv2 cursor_abs_pos;
	t_ftgr_win *win;
};
typedef void (*t_widget_event)(t_widget *widget, struct s_widget_event_infos event_infos);

typedef struct s_widget
{
	t_iv2 pos;
	t_iv2 size;
	bool handle_input;	/* Does this widget receives inputs events */
	bool capture_input; /* Does this widget captures inputs events (doesn't pass them down to childrens) */
	struct s_widget *master;
	U64 master_i;

	U64 childrens_n;
	U64 childrens_del;
	U64 childrens_alloc;
	struct s_widget **childrens;

	union u_widget_data data;
	string name; /* optional, can be NULL */

	U8 drawers_n;
	U64 drawers_alloc;
	t_widget_drawer *drawers;

	bool cached;
	t_ftgr_img *cache;

	void (*destructor)(t_widget *w);

	bool (*widget_proc)(t_widget *w, t_ftgr_ev *ev);
	t_widget_event on_cursor_enter;
	t_widget_event on_cursor_exit;
	t_widget_event on_cursor_click;
	t_widget_event on_cursor_release;
	t_widget_event on_cursor_move;

	bool hovered;
	bool clicked;

	t_iv4 damage;
} t_widget;

t_widget *ftgr_new_widget();
bool ftgr_init_widget(t_widget *widget);
void ftgr_free_widget_recursive(t_widget *widget);
void ftgr_free_widget(t_widget *widget);
bool ftgr_add_wdrawer(t_widget *widget, t_widget_drawer drawer);

bool ftgr_add_widget(t_widget *widget, t_widget *master);
void ftgr_remove_widget(t_widget *widget);

void ftgr_handle_widget_events(t_ftgr_win *win, t_widget *w);

void ftgr_widget_damage(t_widget *root, t_iv4 rect);
bool ftgr_draw_widget_damage(t_ftgr_img *out, t_widget *widget);
void ftgr_draw_widget(t_ftgr_img *out, t_widget *widget);
void ftgr_draw_widget_recursive(t_ftgr_img *out, t_widget *widget);

t_iv2 ftgr_widget_abs_pos(t_widget *widget);
t_iv4 ftgr_widget_rect(t_widget *widget);

/* widgets drawers */
bool ftgr_wdrawer_copy_img_cpu(t_widget *widget, t_ftgr_img *img);
bool ftgr_wdrawer_stretch_img_cpu(t_widget *widget, t_ftgr_img *img);
bool ftgr_wdrawer_fill_rect(t_widget *widget, t_color color);
bool ftgr_wdrawer_draw_rect(t_widget *widget, t_color color);
bool ftgr_wdrawer_draw_text(t_widget *widget, t_bitmap *bitmap, t_text *text, t_color color);
bool ftgr_wdrawer_draw_disc(t_widget *widget, U32 radius, t_color color);

#endif

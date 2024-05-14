/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr_ui.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:47:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/07 17:17:56 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTGR_UI_H

# include "libftgr.h"

#ifndef T_UI_ELEMENT
typedef void *t_ui_element;
#define T_UI_ELEMENT
#endif

#ifndef T_UI_CALLBACK
typedef void (*t_ui_callback)(t_ui_element *ui, void *param1, void *param2);
#define T_UI_CALLBACK
#endif

//Param: t_iv2 pos, NULL
#define UI_MOUSE_ENTER 0
//Param: t_iv2 pos, NULL
#define UI_MOUSE_LEAVE 1
//Param: t_iv2 pos, NULL
#define UI_MOUSE_MOVE 2
//Param: t_iv2 pos, int mousebutton
#define UI_MOUSE_CLICK 3
//Param: t_iv2 pos, int mousebutton
#define UI_MOUSE_RELEASE 4

#define UI_EVENT_MAX (UI_MOUSE_RELEASE + 1)

//Mallocs new t_ui_element
t_ui_element *ftgr_new_ui();

//Sets the callback for a specific event. Returns previous callback
t_ui_callback *ftgr_ui_bind(t_ui_element *ui, S32 event, t_ui_callback callback);

void ftgr_ui_draw_line(t_ui_element *ui, t_iv2 start, t_iv2 end, t_color col);
void ftgr_ui_draw_rect(t_ui_element *ui, t_iv2 c1, t_iv2 c2, t_color col);

//draws the ui
void ftgr_ui_draw(t_ui_element *ui, t_ftgr_img *img);
void ftgr_free_ui(t_ui_element *ui);

void draw_button(t_ftgr_img *img, t_iv2 pos, t_iv2 size, string text, void (*callback)());

#endif
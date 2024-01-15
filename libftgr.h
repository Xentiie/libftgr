/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:58:46 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/13 01:58:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTGR_H
# define LIBFTGR_H

# include "libft.h"

typedef void*	t_ftgr_ctx;
typedef void*	t_ftgr_win;

t_ftgr_ctx	*ftgr_create_ctx();

t_ftgr_win	*ftgr_new_window(t_ftgr_ctx *ctx, t_iv2 size, const_string title);

void		ftgr_loop(t_ftgr_ctx *ctx);
/*
void		ftx11_clear_window(t_ftgr_ctx *xvar, t_ftgr_win *win);

void		ftx11_mouse_move(t_ftgr_ctx *ctx, t_ftgr_win *win, t_iv2 pos);
void		ftx11_mouse_hide(t_ftgr_ctx *ctx, t_ftgr_win *win);
void		ftx11_mouse_show(t_ftgr_ctx *ctx, t_ftgr_win *win);
t_iv2		ftx11_mouse_get_pos(t_ftgr_ctx *ctx, t_ftgr_win *win);

bool		ftx11_is_key_down(t_ftgr_ctx *ctx);
bool		ftx11_is_key_up(t_ftgr_ctx *ctx);
void		ftx11_key_autorepeat(t_ftgr_ctx *ctx, bool active);

t_iv2		ftx11_get_screen_size(t_ftgr_ctx *ctx);
*/


#endif
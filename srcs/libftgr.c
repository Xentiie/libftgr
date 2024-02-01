/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 02:22:03 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/13 02:22:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(FT_WIN32)
# include "libftwin32.h"
# define FTGR_FUNC(f) ftwin32_##f

#elif defined(FT_LINUX)
# include "libftx11.h"
# define FTGR_FUNC(f) ftx11_##f

#endif

#include "libftgr.h"

inline t_ftgr_ctx	*ftgr_create_ctx()
{ return FTGR_FUNC(create_ctx)(); }

inline t_ftgr_win	*ftgr_new_window(t_ftgr_ctx *ctx, t_iv2 size, const_string title)
{ return FTGR_FUNC(new_window)(ctx, size, title); }

inline void		ftgr_loop(t_ftgr_ctx *ctx)
{ FTGR_FUNC(loop)(ctx); }

inline void		ftgr_quit(t_ftgr_ctx *ctx)
{ FTGR_FUNC(quit)(ctx); }

inline void		ftgr_set_quit_handler(t_ftgr_ctx *ctx, void (*handler)())
{ FTGR_FUNC(set_quit_handler)(ctx, handler); }

inline void		ftgr_bring_top(t_ftgr_win *win)
{ FTGR_FUNC(bring_top)(win); }

inline void		ftgr_mouse_move(t_ftgr_ctx *ctx, t_ftgr_win *win, t_iv2 pos)
{ FTGR_FUNC(mouse_move)(ctx, win, pos); }

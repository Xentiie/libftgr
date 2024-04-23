/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_clear_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:36:39 by reclaire          #+#    #+#             */
/*   Updated: 2024/04/16 22:36:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"

void	ftgr_clear_window(t_ftgr_ctx *xvar, t_ftgr_win *win)
{
  XClearWindow(xvar->display, win->window);
  if (xvar->flush)
    XFlush(xvar->display);
}

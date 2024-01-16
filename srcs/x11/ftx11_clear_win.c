/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx11_clear_win.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:20:44 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/09 17:55:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftx11_int.h"

void	ftx11_clear_window(t_ftx11_ctx *xvar, t_ftx11_win *win)
{
  XClearWindow(xvar->display, win->window);
  if (xvar->flush)
    XFlush(xvar->display);
}

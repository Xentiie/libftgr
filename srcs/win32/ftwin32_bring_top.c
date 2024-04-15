/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftwin32_bring_top.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:08:54 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/31 21:08:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftwin32_int.h"

void	ftwin32_bring_top(t_ftwin32_win *win)
{
	if (BringWindowToTop(win->window_handle) == FALSE)
		_ftwin32_error(win->ctx);
	//SetWindowPos(win->window_handle, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

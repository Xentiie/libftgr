/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:45:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/06 15:21:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#include "libftgr.h"
#include <stdio.h>

void ftgr_display_fps(t_ftgr_win *win)
{
	char buffer[100];
	snprintf(buffer, sizeof(buffer), "%.5f", 1.0f / ftgr_delta_time(win->ctx));
	ftgr_set_win_name_infos(win, buffer);
}


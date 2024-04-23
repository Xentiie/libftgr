/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:38:56 by reclaire          #+#    #+#             */
/*   Updated: 2024/04/23 01:30:30 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"

void ftgr_display_fps(t_ftgr_win *win)
{
	char buffer[10];
	snprintf(buffer, sizeof(buffer), "%.5f", 1.0f / ftgr_delta_time(win->ctx));
	ftgr_set_win_name_infos(win, buffer);
}

S32 ftgr_color_to_int(t_color col)
{
	return (((col.a & 0xff) << 24) + ((col.r & 0xff) << 16)
			+ ((col.g & 0xff) << 8) + (col.b & 0xff));
}


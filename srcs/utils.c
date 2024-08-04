/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:45:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/09 00:50:42 by reclaire         ###   ########.fr       */
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

U32 ftgr_color_to_int(t_color col)
{
	return (((col.a & 0xff) << 24) + ((col.r & 0xff) << 16)
			+ ((col.g & 0xff) << 8) + (col.b & 0xff));
}

t_color ftgr_int_to_color(U32 v)
{
	//TODO: different image type
	return (t_color){
		.a = (v >> 24),
		.r = (v >> 16) & 0xFF,
		.g = (v >> 8) & 0xFF,
		.g = v & 0xFF,
	};
}

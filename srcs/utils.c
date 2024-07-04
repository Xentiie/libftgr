/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:45:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/04 16:46:49 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#ifdef FT_OS_WIN
# include "libftgr_win_int.h"
#else
# include "libftgr_x11_int.h"
#endif

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
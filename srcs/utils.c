/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:45:09 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/26 22:38:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#include "libftGFX.h"
#include <stdio.h>

void ftGFX_display_fps(struct s_ftGFX_window *win)
{
	char buffer[100];

	snprintf(buffer, sizeof(buffer), "%.5f", 1.0f / win->ctx->delta_time);
	ftGFX_set_win_name_infos(win, buffer);
}


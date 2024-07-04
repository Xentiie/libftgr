/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_time_win.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:25:39 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/04 16:09:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int_win.h"
#include "libft/time.h"

float ftgr_time(t_ftgr_ctx *ctx)
{
    t_time t;
    clk_get(&t);
    return clk_diff_float(&ctx->global_time, &t);
}

float ftgr_delta_time(t_ftgr_ctx *ctx)
{
    return ctx->delta_time;
}



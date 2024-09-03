/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:49:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/02 03:14:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#ifdef FT_OS_WIN
# include "libftgr_win_int.h"
#else
# include "libftgr_x11_int.h"
#endif

float ftgr_time(t_ftgr_ctx *ctx)
{
    t_time t;
    ft_clk_get(&t);
    return ft_clk_diff_float(&ctx->global_time, &t);
}

float ftgr_delta_time(t_ftgr_ctx *ctx)
{
    return ctx->delta_time;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:49:09 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/26 17:54:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/std.h"
#ifdef FT_OS_WIN
# include "libftgr_win_int.h"
#else
# include "libftGFX_x11.h"
#endif

float ftgr_time(struct s_ftGFX_ctx *ctx)
{
    t_time t;
    ft_clk_get(&t);
    return ft_clk_diff_float(&ctx->global_time, &t);
}

float ftgr_delta_time(struct s_ftGFX_ctx *ctx)
{
    return ctx->delta_time;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:20:53 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/10 06:13:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

inline t_color ftgr_rand_color(U32 seed)
{
	return (t_color){.r = ft_frand(seed) * 255, .g = ft_frand(seed + 1) * 255, .b = ft_frand(seed + 2) * 255, .a = 255};
}

inline t_color ftgr_alpha_blend(t_color under, t_color over)
{
	F32 over_a;
	F32 inv_over_a;
	F32 under_a;

	over_a = (F32)over.a / 255.0F;
	under_a = (F32)under.a / 255.0f;
	inv_over_a = 1.0f - over_a;
	return (t_color){
		.r = over_a * over.r + inv_over_a * under.r * under_a,
		.g = over_a * over.g + inv_over_a * under.g * under_a,
		.b = over_a * over.b + inv_over_a * under.b * under_a,
		.a = (over_a + under_a * inv_over_a) * 255.0f};
}

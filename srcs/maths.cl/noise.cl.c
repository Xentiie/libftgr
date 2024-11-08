/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.cl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 05:43:31 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 15:18:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.cl.h"

F32 ft_noise3(t_v3 p)
{
	return ft_frac(sin(p.x * 112.9898f + p.y * 179.233f + p.z * 237.212f) * 43758.5453f);
}

F32 ft_noise2(t_v2 p)
{
	return ft_noise3(vec3(p.x, p.y, 0));
}

/*
F32	ft_noise2(t_v2 st)
{
	t_v2	i;
	t_v2	f;
	t_v4	abcd;
	t_v2	u;

	f = ft_frac(st);
	i = ft_floor(st);
	abcd.x = ft_frand2(i);
	abcd.y = ft_frand2(i + vec2(1.0, 0.0));
	abcd.z = ft_frand2(i + vec2(0.0, 1.0));
	abcd.w = ft_frand2(i + vec2(1.0, 1.0));
	u = ft_smoothstep(vec2(0, 0), vec2(1, 1), f);
	return (ft_lerp(abcd.x, abcd.y, u.x) + (abcd.z - abcd.x) * u.y * (1.0 - u.x)
		+ (abcd.w - abcd.y) * u.x * u.y);
}
*/

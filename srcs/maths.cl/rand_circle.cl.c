/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_circle.cl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 05:43:03 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 15:18:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.cl.h"

t_v2	ft_rand_circle(U32 seed)
{
	return (vec2(sin(ft_noise2(vec2(seed, 0))), cos(ft_noise2(vec2(seed, 0)) + 1)));
}

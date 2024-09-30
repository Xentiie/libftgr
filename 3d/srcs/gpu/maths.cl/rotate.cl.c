/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 05:12:59 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 05:13:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.cl.h"

t_v2	ft_rotate2(t_v2 v, F32 angle, t_v2 origin)
{
	t_v2	p;
	t_v2	tmp;

	p = v - origin;
	tmp.x = p.x * cos(angle) - p.y * sin(angle);
	tmp.y = p.x * sin(angle) + p.y * cos(angle);
	return (tmp + origin);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bezier.cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:00:59 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 15:06:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.cl.h"

t_v2 ft_bezier_interp(t_v2 p1, t_v2 p2, t_v2 p3, F32 t)
{
	t_v2 tmpa = ft_lerp(p1, p2, t);
	t_v2 tmpb = ft_lerp(p2, p3, t);
	return ft_lerp(tmpa, tmpb, t);
}

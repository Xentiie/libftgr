/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.cl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 05:41:14 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 15:13:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.cl.h"

t_v2 ft_line_intersect(t_v2 l1p1, t_v2 l1p2, t_v2 l2p1, t_v2 l2p2)
{
    F32 s1, s2, b1, b2;
    const F32 epsilon = 1e-6;

    // Check for vertical lines (to avoid division by zero)
    if (fabs(l1p2.x - l1p1.x) < epsilon) {
        // Line 1 is vertical, handle specially
        F32 x = l1p1.x;
        s2 = (l2p2.y - l2p1.y) / (l2p2.x - l2p1.x);  // Slope of line 2
        b2 = l2p1.y - s2 * l2p1.x;                   // Intercept of line 2
        F32 y = s2 * x + b2;                         // Find y using line 2 equation
        return vec2(x, y);
    }

    if (fabs(l2p2.x - l2p1.x) < epsilon) {
        // Line 2 is vertical, handle specially
        F32 x = l2p1.x;
        s1 = (l1p2.y - l1p1.y) / (l1p2.x - l1p1.x);  // Slope of line 1
        b1 = l1p1.y - s1 * l1p1.x;                   // Intercept of line 1
        F32 y = s1 * x + b1;                         // Find y using line 1 equation
        return vec2(x, y);
    }

    // Calculate slopes for both lines
    s1 = (l1p2.y - l1p1.y) / (l1p2.x - l1p1.x);
    s2 = (l2p2.y - l2p1.y) / (l2p2.x - l2p1.x);

    // Check for parallel lines
    if (fabs(s1 - s2) < epsilon) {
        return vec2(FT_F32_QNAN, FT_F32_QNAN);  // No intersection (parallel lines)
    }

    // Calculate intercepts
    b1 = l1p1.y - s1 * l1p1.x;
    b2 = l2p1.y - s2 * l2p1.x;

    // Find intersection point
    F32 x = (b2 - b1) / (s1 - s2);
    F32 y = s1 * x + b1;

    return vec2(x, y);
}

F32	ft_dist_line(t_v2 p, t_v2 s1, t_v2 s2)
{
	t_v2	ab;
	t_v2	cd;
	F32		param;
	t_v2	d;
	t_v2	tmp;

	ab = p - s1;
	cd = s2 - s1;
	param = 1;
	if (ft_dot(cd, cd) != 0)
		param = ft_dot(ab, cd) / ft_dot(cd, cd);
	if (param < 0)
		tmp = vec2(s1.x, s1.y);
	else if (param > 1)
		tmp = vec2(s2.x, s2.y);
	else
		tmp = vec2(s1.x + param * cd.x, s1.y + param * cd.y);
	d = p - tmp;
	return sqrt(d.x * d.x + d.y * d.y);
}

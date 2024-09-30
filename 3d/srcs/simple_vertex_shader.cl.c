/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_vertex_shader.cl.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:34:49 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 08:35:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.cl.h"

t_v4 vertex_shader(t_v3 p, t_mat4x4 world_to_clip)
{
	return ft_mat4x4_mult_v4(world_to_clip, vec4(p.x, p.y, p.z, 1.0f));
}

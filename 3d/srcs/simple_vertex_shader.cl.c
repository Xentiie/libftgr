/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_vertex_shader.cl.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:34:49 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 20:39:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.cl.h"

t_v4 vertex_shader(global U8 *addr, t_mat4x4 model_to_world, t_mat4x4 world_to_clip)
{
	t_v3 p = *(global t_v3 *)addr;

	t_v4 model_pos = ft_mat4x4_mult_v4(model_to_world, vec4(p.x, p.y, p.z, 1.0f));
	return ft_mat4x4_mult_v4(world_to_clip, model_pos);
	//return vec4(p.x, p.y, p.z, 0.0f);
}

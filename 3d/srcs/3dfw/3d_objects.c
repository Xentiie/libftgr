/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_objects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:17:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 12:17:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "3dfw/3dfw.h"

t_mat4x4 object_get_model_to_world(struct s_object obj)
{
	return ft_mat4x4_mult_mat(ft_mat4x4_mult_mat(
		ft_mat4x4_translate_v3(obj.pos),
		ft_mat4x4_scale_v3(obj.scl)),
		ft_mat4x4_rotate_euler(obj.rot));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:04:23 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/13 22:05:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./3d.h"

void draw_grid(struct s_camera cam, t_v3 grid_pos, t_v3 grid_up)
{
	t_v3 near[4];
	t_v3 far[4];

	cam_get_frustum(cam, near, far);
	
	
}

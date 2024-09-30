/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:23:33 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 12:24:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "3dfw/3dfw.h"

void camera_move(t_ftgr_ctx *ctx, struct s_camera *cam)
{
	F32 dtime = ftgr_delta_time(ctx);
	t_v3 cam_right;
	{ /* camera movement */
		t_v3 move = vec3(0, 0, 0);
		move.x = ftgr_is_key_pressed(ctx, 'z') - ftgr_is_key_pressed(ctx, 's');
		move.y = ftgr_is_key_pressed(ctx, ' ') - ftgr_is_key_pressed(ctx, 'c');
		move.z = ftgr_is_key_pressed(ctx, 'd') - ftgr_is_key_pressed(ctx, 'q');
		bool sprint = ftgr_mouse_pressed(ctx, MOUSE_LEFT);

		cam_right = ft_normalize3(ft_cross3(cam->forward, cam->up));
		cam->pos = vec3_add(cam->pos, vec3_scl(cam->forward, move.x * dtime * 10 * (sprint ? 8 : 1)));
		cam->pos = vec3_add(cam->pos, vec3_scl(cam->up, move.y * dtime * 10 * (sprint ? 8 : 1)));
		cam->pos = vec3_add(cam->pos, vec3_scl(cam_right, move.z * dtime * 10 * (sprint ? 8 : 1)));
	}

	{ /* camera rotation */
		t_v3 rotate = vec3(0, 0, 0);
		t_mat4x4 camera_orientation;

		if (ftgr_is_key_pressed(ctx, 'j'))
			rotate.x -= dtime * 0.5f;
		if (ftgr_is_key_pressed(ctx, 'l'))
			rotate.x += dtime * 0.5f;
		if (ftgr_is_key_pressed(ctx, 'k'))
			rotate.y -= dtime * 0.5f;
		if (ftgr_is_key_pressed(ctx, 'i'))
			rotate.y += dtime * 0.5f;

		if (rotate.x != 0.0f || rotate.y != 0.0f || rotate.z != 0.0f)
			camera_orientation = cam_get_orientation(*cam);

		if (rotate.x != 0.0f || rotate.y != 0.0f)
		{
			t_v3 c0 = *(t_v3 *)ft_mat4x4_col(&camera_orientation, 0);
			t_v3 c1 = *(t_v3 *)ft_mat4x4_col(&camera_orientation, 1);
			t_v3 c2 = *(t_v3 *)ft_mat4x4_col(&camera_orientation, 2);

			t_v3 tmp = vec3_sub(vec3_scl(c2, cosf(rotate.x)), vec3_scl(c0, sinf(rotate.x)));

			cam->forward = ft_normalize3(vec3_sub(vec3_scl(c1, sinf(rotate.y)), vec3_scl(tmp, cosf(rotate.y))));
			cam->up = ft_normalize3(vec3_add(vec3_scl(c1, cosf(rotate.y)), vec3_scl(tmp, sinf(rotate.y))));
		}

		if (rotate.z != 0.0f)
		{
			t_v4 up4 = ft_mat4x4_mult_v4(ft_mat4x4_transpose(camera_orientation), vec4(cam->up.x, cam->up.y, cam->up.z, 1.0f));
			t_v4 tmp = ft_mat4x4_mult_v4(camera_orientation, vec4(up4.x * cos(rotate.z) - sin(rotate.z), up4.x * sin(rotate.z) + up4.y * cos(rotate.z), up4.z, 1.0f));
			cam->up = vec3(tmp.x, tmp.y, tmp.z);
		}
	}
}

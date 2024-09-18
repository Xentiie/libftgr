/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:00:56 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/18 20:57:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./3d.h"

t_mat4x4 cam_get_projection(struct s_camera cam)
{
	return ft_mat4x4_mult_mat((t_mat4x4){ /* flip y */
								  1.0f, 0.0f, 0.0f, 0.0f,
								  0.0f, -1.0f, 0.0f, 0.0f,
								  0.0f, 0.0f, 1.0f, 0.0f,
								  0.0f, 0.0f, 0.0f, 1.0f},
							  ft_mat4x4_mult_mat(ft_mat4x4_fit_to_view(vec2(-1, -1), vec2(2, 2), ivec2_flt(cam.surface->size)), ft_mat4x4_perspective(cam.fov, cam.near, cam.far)));
}

t_mat4x4 cam_get_camera_orientation(struct s_camera cam)
{
	/*
	//TODO: utiliser moteur pour visualiser des operations (genre cross())
	a1 = -norm(camera.forward) (arriere)
	a2 = norm(cross(camera.up, a1)) (droite/gauche)
	a3 = norm(cross(a1, a2)) (down je pense)
	*/
	t_v3 a1 = vec3_mul(ft_normalize3(cam.forward), vec3(-1.0f, -1.0f, -1.0f));
	t_v3 a2 = ft_normalize3(ft_cross3(cam.up, a1));
	t_v3 a3 = ft_normalize3(ft_cross3(a1, a2));

	return (t_mat4x4){
		a2.x, a2.y, a2.z, 0.f,
		a3.x, a3.y, a3.z, 0.f,
		a1.x, a1.y, a1.z, 0.f,
		0.f, 0.f, 0.f, 1.f};
}

t_mat4x4 cam_get_world_to_view(struct s_camera cam)
{
	t_mat4x4 camera_orientation = cam_get_camera_orientation(cam);

	t_v4 pos = ft_mat4x4_mult_v4(ft_mat4x4_transpose(camera_orientation), vec4(cam.pos.x, cam.pos.y, cam.pos.z, 1.f));

	return (t_mat4x4){
		camera_orientation.m00, camera_orientation.m01, camera_orientation.m02, 0.f,
		camera_orientation.m10, camera_orientation.m11, camera_orientation.m12, 0.f,
		camera_orientation.m20, camera_orientation.m21, camera_orientation.m22, 0.f,
		-pos.x, -pos.y, -pos.z, 1.f};
}

t_mat4x4 cam_get_world_to_clip(struct s_camera cam)
{
	return ft_mat4x4_mult_mat(cam_get_projection(cam), cam_get_world_to_view(cam));
}

void cam_get_frustum(struct s_camera cam, t_v3 near[4], t_v3 far[4])
{
	t_v2 near_plane_size, far_plane_size;
	t_v3 near_center, far_center;
	t_v3 cam_right;
	F32 aspect_ratio;

	cam_right = ft_normalize3(ft_cross3(cam.forward, cam.up));
	aspect_ratio = (F32)cam.surface->size.x / (F32)cam.surface->size.y;

	F32 a = 2.0f * tanf(ft_radians(cam.fov) / 2.0f);
	near_plane_size.y = a * cam.near * 2.0f;
	near_plane_size.x = near_plane_size.y * aspect_ratio;

	far_plane_size.y = a * cam.far * 2.0f;
	far_plane_size.x = far_plane_size.y * aspect_ratio;

	near_center = vec3_add(cam.pos, vec3_scl(ft_normalize3(cam.forward), cam.near));
	far_center = vec3_add(cam.pos, vec3_scl(ft_normalize3(cam.forward), cam.far));

	t_v3 cam_right_near = vec3_scl(cam_right, (near_plane_size.x / 2.0f));
	t_v3 cam_up_near = vec3_scl(cam.up, (near_plane_size.y / 2.0f));

	if (near)
	{
		near[0] = vec3_sub(near_center, vec3_add(cam_right_near, cam_up_near));
		near[1] = vec3_add(near_center, vec3_sub(cam_right_near, cam_up_near));
		near[2] = vec3_add(near_center, vec3_add(cam_right_near, cam_up_near));
		near[3] = vec3_sub(near_center, vec3_sub(cam_right_near, cam_up_near));
	}

	if (far)
	{
		far[0] = vec3_sub(far_center, vec3_add(vec3_scl(cam_right, (far_plane_size.x / 2)), vec3_scl(cam.up, far_plane_size.y / 2.0f)));
		far[1] = vec3_add(far_center, vec3_sub(vec3_scl(cam_right, (far_plane_size.x / 2)), vec3_scl(cam.up, far_plane_size.y / 2.0f)));
		far[2] = vec3_add(far_center, vec3_add(vec3_scl(cam_right, (far_plane_size.x / 2)), vec3_scl(cam.up, far_plane_size.y / 2.0f)));
		far[3] = vec3_sub(far_center, vec3_sub(vec3_scl(cam_right, (far_plane_size.x / 2)), vec3_scl(cam.up, far_plane_size.y / 2.0f)));
	}
}

bool clip_line_with_cam(struct s_camera cam, t_v3 *p1, t_v3 *p2)
{
	t_v3 near[4];
	t_v3 far[4];
	cam_get_frustum(cam, near, far);

	t_v4 planes[6];
	/* near plane */ planes[0] = get_plane_eq(near[0], near[1], near[2]);
	/* far plane */ planes[1] = get_plane_eq(far[2], far[1], far[1]);

	/* left plane */ planes[2] = get_plane_eq(far[3], far[0], near[0]);
	/* right plane */ planes[3] = get_plane_eq(near[1], far[1], far[2]);

	/* bottom plane */ planes[4] = get_plane_eq(near[0], far[0], far[1]);
	/* top plane */ planes[5] = get_plane_eq(near[2], far[2], far[3]);

	for (S32 i = 0; i < 6; i++)
	{
		t_v4 plane = planes[i];

		// Calculate distances from both points to the plane
		F32 d1 = plane.x * p1->x + plane.y * p1->y + plane.z * p1->z + plane.w;
		F32 d2 = plane.x * p2->x + plane.y * p2->y + plane.z * p2->z + plane.w;

		if (d1 > 0 && d2 > 0)
			continue;

		// Both points are outside, discard the line
		if (d1 < 0 && d2 < 0)
			return FALSE;

		F32 t = d1 / (d1 - d2);
		t_v3 intersect = vec3(
			p1->x + t * (p2->x - p1->x),
			p1->y + t * (p2->y - p1->y),
			p1->z + t * (p2->z - p1->z));

		if (d1 > 0 && d2 < 0)
			*p2 = intersect;
		else if (d1 < 0 && d2 > 0)
			*p1 = intersect;
	}
	return TRUE;
}

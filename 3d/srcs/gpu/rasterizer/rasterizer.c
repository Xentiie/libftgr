/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:07:37 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/08 04:34:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterizer_private.h"
#include "3dfw/3dfw.h"
#include "gpu/clc/clc.h"
#include "gpu/clfw/clfw.h"

#include "libft/io.h"

#include <stdio.h>

static t_v4 *launch_tris_setup(Pipeline pipe, struct s_object object, struct s_camera cam)
{
	t_mat4x4 world_to_clip;
	t_mat4x4 model_to_world;

	world_to_clip = cam_get_world_to_clip(cam);
	model_to_world = object_get_model_to_world(object);

	U64 i = 7;
	if (
		!clfw_set_kernel_arg(pipe->vert_shdr, 7, sizeof(t_iv4), (&(t_iv4){cam.pos.x, cam.pos.y, cam.pos.z, 0.0f})) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, 8, sizeof(t_mat4x4), &model_to_world) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, 9, sizeof(t_mat4x4), &world_to_clip))
	{
		printf("couldn't set kernel arg\n");
		exit(1);
	}

	U64 local_work_size = 8;
	U64 global_work_size = object.tris_cnt + (local_work_size - object.tris_cnt % local_work_size);
	if (!clfw_enqueue_nd_range_kernel(pipe->device->queue, pipe->vert_shdr, 1, &(U64){0}, &global_work_size, &local_work_size, 0, NULL, NULL))
	{
		printf("couldn't exec kernel\n");
		exit(1);
	}

	if (!clfw_finish(pipe->device->queue))
		exit(1);

	U32 subtris;
	clfw_enqueue_read_buffer(pipe->device->queue, pipe->atm_subtris, TRUE, 0, sizeof(subtris), &subtris, 0, NULL, NULL);
	t_v4 *interphase_out = malloc(subtris * sizeof(t_v4));
	clfw_enqueue_read_buffer(pipe->device->queue, pipe->interphase_buffer, TRUE, 0, subtris * sizeof(t_v4), interphase_out, 0, NULL, NULL);

	printf("atomic: %u\n", subtris);
	return interphase_out;
}

void pipeline_execute(Pipeline pipe, struct s_object object, struct s_camera cam)
{
	if (!pipeline_prepare(pipe))
		return;

	t_v4 *verts_4 = launch_tris_setup(pipe, object, cam);
	if (!verts_4)
		return;

	for (U64 i = 0; i < object.tris_cnt; i++)
	{
		t_v4 p1 = verts_4[object.tris[i].x];
		t_v4 p2 = verts_4[object.tris[i].y];
		t_v4 p3 = verts_4[object.tris[i].z];

		t_v2 screen_p1;
		t_v2 screen_p2;
		t_v2 screen_p3;

		screen_p1.x = floorf((p1.x + 1.0f) / 2.0f * cam.surface->size.x);
		screen_p1.y = floorf((p1.y + 1.0f) / 2.0f * cam.surface->size.y);

		screen_p2.x = floorf((p2.x + 1.0f) / 2.0f * cam.surface->size.x);
		screen_p2.y = floorf((p2.y + 1.0f) / 2.0f * cam.surface->size.y);

		screen_p3.x = floorf((p3.x + 1.0f) / 2.0f * cam.surface->size.x);
		screen_p3.y = floorf((p3.y + 1.0f) / 2.0f * cam.surface->size.y);

		ftgr_draw_line(cam.surface, vec2_int(screen_p1), vec2_int(screen_p2), COL_DARK_BLUE);
		ftgr_draw_line(cam.surface, vec2_int(screen_p2), vec2_int(screen_p3), COL_DARK_BLUE);
		ftgr_draw_line(cam.surface, vec2_int(screen_p3), vec2_int(screen_p1), COL_DARK_BLUE);
	}

	free(verts_4);
}

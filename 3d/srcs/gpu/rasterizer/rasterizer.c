/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:07:37 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/04 09:27:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "3dfw/3dfw.h"
#include "gpu/rasterizer/rasterizer.h"
#include "gpu/clc/clc.h"
#include "gpu/clfw/clfw.h"

#include "libft/io.h"

#include <stdio.h>

static t_v4 *launch_tris_setup(ClDevice *device, cl_kernel vertex_shader, struct s_object object, struct s_camera cam)
{
	t_mat4x4 world_to_clip = cam_get_world_to_clip(cam);

	t_v4 *verts_4 = malloc(sizeof(t_v4) * object.verts_cnt);
	for (U64 i = 0; i < object.verts_cnt; i++)
		verts_4[i] = vec4(object.verts[i].x, object.verts[i].y, object.verts[i].z, 0.0f);
	S32 sublines_st = 0;

	cl_mem verts_buf = clfw_create_buffer(device->ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_v4) * object.verts_cnt, verts_4);
	cl_mem tris_buf = clfw_create_buffer(device->ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_iv3) * object.tris_cnt, object.tris);
	cl_mem atm_sublines = clfw_create_buffer(device->ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(S32), &sublines_st);
	cl_mem out_buf = clfw_create_buffer(device->ctx, CL_MEM_READ_WRITE, sizeof(t_v4) * object.verts_cnt, NULL);

	t_mat4x4 model_to_world = object_get_model_to_world(object);
	U64 i = 0;
	if (
		!clfw_set_kernel_arg(vertex_shader, i++, sizeof(cl_mem), &verts_buf) ||
		!clfw_set_kernel_arg(vertex_shader, i++, sizeof(U32), &(U32){sizeof(t_v4)}) ||
		!clfw_set_kernel_arg(vertex_shader, i++, sizeof(cl_mem), &tris_buf) ||
		!clfw_set_kernel_arg(vertex_shader, i++, sizeof(U32), &object.tris_cnt) ||
		!clfw_set_kernel_arg(vertex_shader, i++, sizeof(cl_mem), &out_buf) ||
		!clfw_set_kernel_arg(vertex_shader, i++, sizeof(U32), &(U32){sizeof(t_v4) * object.verts_cnt}) ||
		!clfw_set_kernel_arg(vertex_shader, i++, sizeof(cl_mem), &atm_sublines) ||
		!clfw_set_kernel_arg(vertex_shader, i++, sizeof(t_iv4), (&(t_iv4){cam.pos.x, cam.pos.y, cam.pos.z, 0.0f})) ||
		!clfw_set_kernel_arg(vertex_shader, i++, sizeof(t_mat4x4), &model_to_world) ||
		!clfw_set_kernel_arg(vertex_shader, i++, sizeof(t_mat4x4), &world_to_clip)
	)
	{
		printf("couldn't set kernel arg\n");
		exit(1);
	}

	U64 local_work_size = 8;
	U64 global_work_size = object.tris_cnt + (local_work_size - object.tris_cnt % local_work_size);
	if (!clfw_enqueue_nd_range_kernel(device->queue, vertex_shader, 1, &(U64){0}, &global_work_size, &local_work_size, 0, NULL, NULL))
	{
		printf("couldn't exec kernel\n");
		exit(1);
	}

	if (!clfw_finish(device->queue))
	{
		printf("clFinish didn't work\n");
		exit(1);
	}

	clfw_enqueue_read_buffer(device->queue, atm_sublines, TRUE, 0, sizeof(S32), &sublines_st, 0, NULL, NULL);
	clfw_enqueue_read_buffer(device->queue, out_buf, TRUE, 0, sizeof(t_v4) * object.verts_cnt, verts_4, 0, NULL, NULL);

	clfw_release_mem_object(verts_buf);
	clfw_release_mem_object(tris_buf);
	clfw_release_mem_object(atm_sublines);
	clfw_release_mem_object(out_buf);

	printf("atomic: %d\n", sublines_st);
	return verts_4;
}

void render_mesh_gpu(
	cl_kernel vertex_shader,
	ClDevice *device,
	struct s_object object,
	struct s_camera cam)
{
	t_v4 *verts_4 = launch_tris_setup(device, vertex_shader, object, cam);
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

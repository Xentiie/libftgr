/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:07:37 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 05:16:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterizer_private.h"
#include "3dfw/3dfw.h"
#include "clfw/clc.h"

#include "libft/io.h"

#include <stdio.h>

float edgeFunction(t_v2 a, t_v2 b, t_v2 c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

static void draw_bins(t_ftgr_img *img, t_v4 *tris, U32 tris_cnt, t_iv2 tile_size)
{
	for (U32 i = 0; i < tris_cnt; i++)
	{
		t_v2 p1;
		t_v2 p2;
		t_v2 p3;

		p1.x = floorf((tris[i * 3 + 0].x + 1.0f) / 2.0f * img->size.x);
		p1.y = floorf((tris[i * 3 + 0].y + 1.0f) / 2.0f * img->size.y);

		p2.x = floorf((tris[i * 3 + 1].x + 1.0f) / 2.0f * img->size.x);
		p2.y = floorf((tris[i * 3 + 1].y + 1.0f) / 2.0f * img->size.y);

		p3.x = floorf((tris[i * 3 + 2].x + 1.0f) / 2.0f * img->size.x);
		p3.y = floorf((tris[i * 3 + 2].y + 1.0f) / 2.0f * img->size.y);

		t_v2 bbox_min = vec2_div(ft_fmin2_3(p1, p2, p3), ivec2_flt(tile_size));
		t_v2 bbox_max = vec2_div(ft_fmax2_3(p1, p2, p3), ivec2_flt(tile_size));

		bbox_min = vec2(floor(bbox_min.x), floor(bbox_min.y)); // floor
		bbox_max = vec2(ceil(bbox_max.x), ceil(bbox_max.y));
		for (S32 x = bbox_min.x; x < bbox_max.x; x++)
		{
			for (S32 y = bbox_min.y; y < bbox_max.y; y++)
			{
				t_iv2 begin = ft_imax2(ivec2(x * tile_size.x, y * tile_size.y), ivec2(0, 0));
				t_iv2 end = ft_imin2(ivec2(begin.x + tile_size.x, begin.y + tile_size.y), img->size);
				for (S32 _x = begin.x; _x < end.x; _x++)
					for (S32 _y = begin.y; _y < end.y; _y++)
						*ftgr_get_pixel_addr(img, _x, _y) = 0x646464;
			}
		}
	}
}

static bool launch_tris_setup(Pipeline pipe, struct s_object object, struct s_camera cam)
{
	t_mat4x4 world_to_clip;
	t_mat4x4 model_to_world;

	world_to_clip = cam_get_world_to_clip(cam);
	model_to_world = object_get_model_to_world(object);

	cl_mem debug_buf = clfw_create_buffer(pipe->device->ctx, CL_MEM_READ_WRITE, sizeof(t_v4), NULL);

	U64 i = 7;
	if (
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(t_v4), (&(t_v4){cam.pos.x, cam.pos.y, cam.pos.z, 0.0f})) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(t_mat4x4), &model_to_world) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(t_mat4x4), &world_to_clip) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(cl_mem), &debug_buf))
	{
		printf("couldn't set tris setup kernel arg\n");
		return FALSE;
	}

	U64 local_work_size = 8;
	U64 global_work_size = object.tris_cnt + (local_work_size - object.tris_cnt % local_work_size);
	if (!clfw_enqueue_nd_range_kernel(pipe->device->queue, pipe->vert_shdr, 1, &(U64){0}, &global_work_size, &local_work_size, 0, NULL, NULL))
	{
		printf("couldn't exec tris setup kernel\n");
		return FALSE;
	}

	clfw_release_mem_object(debug_buf);

	if (!clfw_finish(pipe->device->queue))
		return FALSE;

	return TRUE;
}

void launch_bin_raster(Pipeline pipe)
{
	
}

void pipeline_execute(Pipeline pipe, struct s_object object, struct s_camera cam)
{
	if (!pipeline_prepare(pipe))
		return;

	if (!launch_tris_setup(pipe, object, cam))
		return FALSE;
	launch_bin_raster(pipe);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_rasterizer_gpu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:07:37 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 09:15:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "3d.h"
#include "../../3d.h"
#include "gpu/rasterizer/rasterizer.h"
#include "gpu/clc/clc.h"

#include "libft/io.h"

#include <stdio.h>

void ft3d_draw_lines(
	cl_kernel vertex_shader,
	cl_context ctx, cl_command_queue queue,
	t_v3 *points, U64 points_cnt, t_iv2 *indices, U64 indices_cnt,
	struct s_camera cam)
{
	S32 err;
	t_mat4x4 world_to_clip = cam_get_world_to_clip(cam);

	t_v4 *points_4 = malloc(sizeof(t_v4) * points_cnt);
	for (U64 i = 0; i < points_cnt; i++)
		points_4[i] = vec4(points[i].x, points[i].y, points[i].z, 0.0f);
	cl_mem points_buf = clCreateBuffer(ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_v4) * points_cnt, points_4, &err);
	CHK_CLCALL(return);

	cl_mem indices_buf = clCreateBuffer(ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_iv2) * indices_cnt, indices, &err);
	CHK_CLCALL(return);

	S32 sublines_st = 0;
	cl_mem atm_sublines = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(S32), &sublines_st, &err);
	CHK_CLCALL(return);

	cl_mem out_buf = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY, sizeof(t_v4) * points_cnt, NULL, &err);
	CHK_CLCALL(return);

	err = clSetKernelArg(vertex_shader, 0, sizeof(cl_mem), &points_buf);
	CHK_CLCALL(return);
	err = clSetKernelArg(vertex_shader, 1, sizeof(U64), &points_cnt);
	CHK_CLCALL(return);
	err = clSetKernelArg(vertex_shader, 2, sizeof(cl_mem), &indices_buf);
	CHK_CLCALL(return);
	err = clSetKernelArg(vertex_shader, 3, sizeof(U64), &indices_cnt);
	CHK_CLCALL(return);
	err = clSetKernelArg(vertex_shader, 4, sizeof(cl_mem), &atm_sublines);
	CHK_CLCALL(return);
	err = clSetKernelArg(vertex_shader, 5, sizeof(cl_mem), &out_buf);
	CHK_CLCALL(return);
	err = clSetKernelArg(vertex_shader, 6, sizeof(t_mat4x4), &world_to_clip);
	CHK_CLCALL(return);

	err = clEnqueueNDRangeKernel(queue, vertex_shader, 1, &(size_t){0}, &indices_cnt, &(size_t){1}, 0, NULL, NULL);
	CHK_CLCALL(return);

	err = clEnqueueReadBuffer(queue, atm_sublines, TRUE, 0, sizeof(S32), &sublines_st, 0, NULL, NULL);
	CHK_CLCALL(return);
	err = clEnqueueReadBuffer(queue, out_buf, TRUE, 0, sizeof(t_v4) * points_cnt, points_4, 0, NULL, NULL);
	CHK_CLCALL(return);
	clReleaseMemObject(points_buf);
	clReleaseMemObject(indices_buf);
	clReleaseMemObject(atm_sublines);
	clReleaseMemObject(out_buf);

	for (U64 i = 0; i < indices_cnt; i++)
	{
		t_v4 p1 = points_4[indices[i].x];
		t_v4 p2 = points_4[indices[i].y];

		t_v2 rcpW = vec2(1.0f / p1.w, 1.0f / p2.w);
		t_v2 screen_p1;
		t_v2 screen_p2;

		screen_p1.x = floorf((p1.x * rcpW.x + 1.0f) / 2.0f * cam.surface->size.x);
		screen_p1.y = floorf((p1.y * rcpW.x + 1.0f) / 2.0f * cam.surface->size.y);

		screen_p2.x = floorf((p2.x * rcpW.y + 1.0f) / 2.0f * cam.surface->size.x);
		screen_p2.y = floorf((p2.y * rcpW.y + 1.0f) / 2.0f * cam.surface->size.y);

		ftgr_draw_line(cam.surface, vec2_int(screen_p1), vec2_int(screen_p2), COL_DARK_BLUE);
	}

	free(points_4);
}

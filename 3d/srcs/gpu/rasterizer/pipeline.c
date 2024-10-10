/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:03:40 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/09 15:19:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterizer_private.h"

Pipeline pipeline_init(ClDevice *device)
{
	Pipeline pipe;
	
	if (UNLIKELY((pipe = malloc(sizeof(struct s_pipeline))) == NULL))
		return NULL;
	ft_bzero(pipe, sizeof(struct s_pipeline));

	pipe->device = device;
	return pipe;
}

void pipeline_free(Pipeline pipe)
{
	if (pipe->frgm_shdr)
		clfw_release_kernel(pipe->frgm_shdr);
	if (pipe->vert_shdr)
		clfw_release_kernel(pipe->vert_shdr);
	if (pipe->shader_prog)
		clfw_release_program(pipe->shader_prog);
	free(pipe);
}

ProgramBuilder pipeline_shader_builder(Pipeline pipe, LibraryCache cache)
{
	ProgramBuilder builder;
	
	if (UNLIKELY((builder = clc_builder_init(pipe->device)) == NULL))
		return NULL;
	if (!clc_executable_begin(builder))
		goto exit_err;
	if (!clc_ingest_library(builder, cache, "maths.cl.h"))
		goto exit_err;


	if (UNLIKELY(!clc_ingest_file(builder, "srcs/gpu/rasterizer/tris_setup.cl.c")))
		goto exit_err;
	//if (UNLIKELY(!clc_ingest_file(builder, "srcs/gpu/rasterizer/tris_raster.cl.c")))
	//	goto exit_err;

	return builder;
exit_err:
	clc_builder_destroy(builder);
	return NULL;
}

bool pipeline_link_shader(Pipeline pipe, ProgramBuilder builder)
{
	pipe->shader_prog = clc_end(builder);
	clc_builder_destroy(builder);
	if (pipe->shader_prog == NULL)
		return FALSE;

	pipe->vert_shdr = clfw_create_kernel(pipe->shader_prog, "tris_setup");
	//pipe->frgm_shdr = clfw_create_kernel(pipe->shader_prog, "fragment_main");
	pipe->dirty = TRUE;
	return TRUE;
}

void pipeline_set_vertex_stride(Pipeline pipe, U32 stride)
{
	pipe->vert_stride = stride;
}

bool pipeline_buffers_init(Pipeline pipe, U64 tris_count_hint)
{
	if (tris_count_hint == 0)
		tris_count_hint = 2000;

	pipe->verts_buffer_alloc = pipe->vert_stride * tris_count_hint * 3;
	pipe->verts_buffer = clfw_create_buffer(pipe->device->ctx, CL_MEM_READ_ONLY, pipe->verts_buffer_alloc, NULL);

	pipe->tris_buffer_alloc = sizeof(S32) * tris_count_hint;
	pipe->tris_buffer = clfw_create_buffer(pipe->device->ctx, CL_MEM_READ_ONLY, pipe->tris_buffer_alloc, NULL);

	pipe->interphase_buffer_alloc = sizeof(t_v4) * tris_count_hint * 3;
	pipe->interphase_buffer = clfw_create_buffer(pipe->device->ctx, CL_MEM_READ_WRITE, pipe->interphase_buffer_alloc, NULL);

	pipe->atm_subtris = clfw_create_buffer(pipe->device->ctx, CL_MEM_READ_WRITE, sizeof(U32), NULL);

	if (pipe->verts_buffer == NULL || pipe->tris_buffer == NULL || pipe->interphase_buffer == NULL || pipe->atm_subtris)
		return FALSE;

	pipe->dirty = TRUE;
	return TRUE;
}

bool pipeline_fill_verts(Pipeline pipe, void *buffer, U32 count)
{
	if (pipe->verts_buffer_alloc < count)
	{
		if (pipe->verts_buffer != NULL)
			clfw_release_mem_object(pipe->verts_buffer);
		pipe->verts_buffer_alloc = pipe->vert_stride * count;
		pipe->verts_buffer = clfw_create_buffer(pipe->device->ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, pipe->verts_buffer_alloc, buffer);
		return pipe->verts_buffer != NULL;
	}
	else
		return clfw_enqueue_write_buffer(pipe->device->queue, pipe->verts_buffer, TRUE, 0, pipe->vert_stride * count, buffer, 0, NULL, NULL);
}

bool pipeline_fill_tris(Pipeline pipe, void *buffer, U32 count)
{
	pipe->tris_cnt = count;
	if (pipe->tris_buffer_alloc < count)
	{
		if (pipe->tris_buffer != NULL)
			clfw_release_mem_object(pipe->tris_buffer);
		pipe->tris_buffer_alloc = sizeof(t_iv3) * count;
		pipe->tris_buffer = clfw_create_buffer(pipe->device->ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, pipe->tris_buffer_alloc, buffer);
		return pipe->tris_buffer != NULL;
	}
	else
		return clfw_enqueue_write_buffer(pipe->device->queue, pipe->tris_buffer, TRUE, 0, sizeof(t_iv3) * count, buffer, 0, NULL, NULL);

}

bool pipeline_set_arg(Pipeline pipe)
{
	U32 i;

	ASSERT(pipe != NULL, FALSE)
	ASSERT(pipe->vert_shdr != NULL, FALSE)
	//ASSERT(pipe->frgm_shdr != NULL, FALSE)
	ASSERT(pipe->verts_buffer != NULL, FALSE)
	ASSERT(pipe->verts_buffer_alloc != 0, FALSE)
	ASSERT(pipe->tris_buffer != NULL, FALSE)
	ASSERT(pipe->tris_buffer_alloc != 0, FALSE)
	ASSERT(pipe->interphase_buffer != NULL, FALSE)
	ASSERT(pipe->interphase_buffer_alloc != 0, FALSE)
	ASSERT(pipe->atm_subtris != NULL, FALSE)

	i = 0;
	if (
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(cl_mem), &pipe->verts_buffer) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(U32), &pipe->vert_stride) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(cl_mem), &pipe->tris_buffer) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(U32), &pipe->tris_cnt) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(cl_mem), &pipe->interphase_buffer) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(U32), &pipe->interphase_buffer_alloc) ||
		!clfw_set_kernel_arg(pipe->vert_shdr, i++, sizeof(cl_mem), &pipe->atm_subtris)
	)
	{
		rast_error("couldn't set vertex shader args\n");
		return FALSE;
	}

	pipe->dirty = FALSE;
	return TRUE;
}

bool pipeline_prepare(Pipeline pipe)
{
	S32 zero = 0;

	if (pipe->dirty)
	{
		if (!pipeline_set_arg(pipe))
			return FALSE;
	}

	if (!clfw_enqueue_write_buffer(pipe->device->queue, pipe->atm_subtris, TRUE, 0, sizeof(U32), &zero, 0, NULL, NULL))
		return FALSE;

	return TRUE;
}

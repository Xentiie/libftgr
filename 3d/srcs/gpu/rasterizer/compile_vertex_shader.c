/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_vertex_shader.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:35:33 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 09:19:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gpu/clc/clc.h"
#include "gpu/cl_errors/cl_errors.h"
#include "log/log.h"

ProgramBuilder vertex_shader_begin(cl_context ctx, cl_device_id device, LibraryCache cache)
{
	ProgramBuilder builder = clc_builder_init(ctx, device);
	if (UNLIKELY(builder == NULL))
		return NULL;

	if (UNLIKELY(clc_executable_begin(builder) == FALSE))
		goto quit_error;

	if (UNLIKELY(clc_ingest_library(builder, cache, "maths.cl.h") == FALSE))
		goto quit_error;
	
	if (UNLIKELY(clc_ingest_file(builder, "srcs/gpu/rasterizer/lines_setup.cl.c") == FALSE))
		goto quit_error;
	return builder;

quit_error:
	clc_builder_destroy(builder);
	return NULL;
}

cl_kernel vertex_shader_end(ProgramBuilder builder, cl_program *out_program)
{
	S32 err;
	cl_program vert_shader = clc_end(builder);
	clc_builder_destroy(builder);
	if (UNLIKELY(vert_shader == NULL))
		return NULL;

	cl_kernel kernel = clCreateKernel(vert_shader, "vertex_main", &err);
	CHK_CLCALL(return NULL);

	if (out_program)
		*out_program = vert_shader;
	return kernel;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:13:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 14:53:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "utils.h"

ProgramBuilder clc_builder_init(cl_context ctx, cl_device_id device)
{
	ProgramBuilder builder = malloc(sizeof(struct s_program_builder));
	if (UNLIKELY(builder == NULL))
	{
		clc_error("program builder: out of memory\n");
		return NULL;
	}
	clc_debug("created builder: %s%p"FT_CRESET"\n", get_unique_col((U64)builder), builder);
	ft_memset(builder, 0, sizeof(struct s_program_builder));

	builder->ctx = ctx;
	builder->device = device;

	builder->headers_n = 0;
	builder->headers_alloc = 1;
	builder->headers_names = malloc(sizeof(string *) * builder->headers_alloc);
	builder->headers_programs = malloc(sizeof(cl_program *) * builder->headers_alloc);
	if (UNLIKELY(builder->headers_names == NULL || builder->headers_programs == NULL))
	{
		log_error(NULL, "out of memory: can't init headers array \n");
		clc_builder_destroy(builder);
		return NULL;
	}

	if (UNLIKELY(clc_include_header(builder, "srcs/gpu/clc/clc.cl.h") == FALSE))
	{
		clc_builder_destroy(builder);
		return NULL;
	}

	return builder;
}

bool clc_builder_destroy(ProgramBuilder builder)
{
	clc_debug("destroying builder: %s%p"FT_CRESET"\n", get_unique_col((U64)builder), builder);
	for (U64 i = 0; i < builder->headers_n; i++)
	{
		//TODO:
		//free(builder->headers_names[i]);
		clReleaseProgram(builder->headers_programs[i]);
	}
	for (U64 i = 0; i < builder->programs_n; i++)
		clReleaseProgram(builder->programs[i].prog);

	free(builder->headers_names);
	free(builder->headers_programs);
	free(builder->programs);
	free(builder);
	return TRUE;
}

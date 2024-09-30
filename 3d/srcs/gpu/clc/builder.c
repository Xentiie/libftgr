/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:13:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 09:20:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"

ProgramBuilder clc_builder_init(cl_context ctx, cl_device_id device)
{
	ProgramBuilder builder = malloc(sizeof(struct s_program_builder));
	if (UNLIKELY(builder == NULL))
	{
		clc_error("program builder: out of memory\n");
		return NULL;
	}
	ft_memset(builder, 0, sizeof(struct s_program_builder));

	builder->ctx = ctx;
	builder->device = device;

	//	array_init(builder->includes, builder->includes_n, builder->includes_alloc,
	//			   (free(builder); free(builder->headers); return NULL));

	builder->headers_n = 0;
	builder->headers_alloc = 1;
	builder->headers_names = malloc(sizeof(string *) * builder->headers_alloc);
	builder->headers_programs = malloc(sizeof(cl_program *) * builder->headers_alloc);
	if (UNLIKELY(builder->headers_names == NULL || builder->headers_programs == NULL))
	{
		log_error(NULL, "out of memory: can't init headers array \n");
		free(builder->headers_names);
		free(builder->headers_programs);
		return NULL;
	}

	return builder;
}

bool clc_builder_destroy(ProgramBuilder builder)
{
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:13:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/08 03:31:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "utils.h"

ProgramBuilder clc_builder_init(ClDevice *device)
{
	ProgramBuilder builder;

	ASSERT(device != NULL, NULL)
	ASSERT(device->ctx != NULL, NULL)
	ASSERT(device->device_id != NULL, NULL)

	if (UNLIKELY((builder = malloc(sizeof(struct s_program_builder))) == NULL))
	{
		clc_error("program builder: out of memory\n");
		return NULL;
	}
	ft_bzero(builder, sizeof(struct s_program_builder));
	clc_debug("created builder: %s%p" FT_CRESET "\n", get_unique_col((U64)builder), builder);

	builder->device = device;

	builder->headers_n = 0;
	builder->headers_alloc = 1;
	builder->headers_names = malloc(sizeof(string *) * builder->headers_alloc);
	builder->headers_programs = malloc(sizeof(cl_program *) * builder->headers_alloc);
	if (UNLIKELY(builder->headers_names == NULL || builder->headers_programs == NULL))
	{
		clc_error("program builder: out of memory\n");
		clc_builder_destroy(builder);
		return NULL;
	}

	if (UNLIKELY(clc_include_header(builder, "srcs/gpu/clfw.cl/clfw.cl.h") == FALSE) ||
		UNLIKELY(clc_ingest_file(builder, "srcs/gpu/clfw.cl/clfw.cl.c") == FALSE))
	{
		clc_builder_destroy(builder);
		return NULL;
	}

	return builder;
}

bool clc_builder_destroy(ProgramBuilder builder)
{
	ASSERT(builder != NULL, FALSE);

	clc_debug("destroying builder: %s%p" FT_CRESET "\n", get_unique_col((U64)builder), builder);
	for (U64 i = 0; i < builder->headers_n; i++)
	{
		// TODO:
		// free(builder->headers_names[i]);
		clfw_release_program(builder->headers_programs[i]);
	}
	for (U64 i = 0; i < builder->programs_n; i++)
		clfw_release_program(builder->programs[i].prog);

	free(builder->headers_names);
	free(builder->headers_programs);
	free(builder->programs);
	free(builder);
	return TRUE;
}

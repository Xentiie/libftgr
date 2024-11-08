/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:13:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 05:36:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "libft/ansi.h"

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
	builder->headers_alloc = 2;
	builder->headers_names = malloc(sizeof(string *) * builder->headers_alloc);
	builder->headers_programs = malloc(sizeof(cl_program *) * builder->headers_alloc);
	if (UNLIKELY(builder->headers_names == NULL || builder->headers_programs == NULL))
	{
		clc_error("program builder: out of memory\n");
		goto exit_err;
	}

	builder->programs_n = 0;
	builder->programs_alloc = 2;
	if (UNLIKELY((builder->programs = malloc(sizeof(t_program) * builder->programs_alloc)) == NULL))
	{
		clc_error("program builder: out of memory\n");
		goto exit_err;
	}

	builder->libraries_n = 0;
	builder->libraries_alloc = 2;
	if (UNLIKELY((builder->libraries = malloc(sizeof(struct s_library) * builder->libraries_alloc)) == NULL))
	{
		clc_error("program builder: out of memory\n");
		goto exit_err;
	}

	{ /* building cl framework (clfw.cl and maths.cl) */
		cl_program lib_prog;

		{ /* clfw */
			if (UNLIKELY(!clc_library_begin(builder)))
				goto exit_err;

			printf("%p\n", header_src(clfw));
			if (UNLIKELY(clc_include_header_src(builder, "clfw.cl.h", header_src(clfw)) == FALSE) ||
				UNLIKELY(clc_ingest_str(builder, file_src(clfw)) == FALSE))
				goto exit_err;

			if (UNLIKELY((lib_prog = clc_end(builder)) == NULL))
				goto exit_err;

			if (UNLIKELY(!clc_cache_lib(builder, "clfw.cl.h", lib_prog, "clfw")))
				goto exit_err;

			clfw_release_program(lib_prog);
		}

		{ /* maths */
			if (UNLIKELY(!clc_library_begin(builder)))
				goto exit_err;

			if (UNLIKELY(clc_include_header_src(builder, "maths.cl.h", header_src(maths)) == FALSE) ||
				UNLIKELY(clc_ingest_str(builder, file_src(bezier)) == FALSE) ||
				UNLIKELY(clc_ingest_str(builder, file_src(lines)) == FALSE) ||
				UNLIKELY(clc_ingest_str(builder, file_src(mat4x4)) == FALSE) ||
				UNLIKELY(clc_ingest_str(builder, file_src(noise)) == FALSE) ||
				UNLIKELY(clc_ingest_str(builder, file_src(rand_circle)) == FALSE) ||
				UNLIKELY(clc_ingest_str(builder, file_src(rotate)) == FALSE))
				goto exit_err;

			if (UNLIKELY((lib_prog = clc_end(builder)) == NULL))
				goto exit_err;

			if (UNLIKELY(!clc_cache_lib(builder, "maths.cl.h", lib_prog, "maths")))
				goto exit_err;

			clfw_release_program(lib_prog);
		}
	}

	return builder;
exit_err:
	clc_builder_destroy(builder);
	return NULL;
}

ProgramBuilder clc_builder_init_from(ProgramBuilder pb)
{
	ProgramBuilder builder;

	ASSERT(pb != NULL, NULL);

	if (UNLIKELY((builder = malloc(sizeof(struct s_program_builder))) == NULL))
		goto exit_omem;
	clc_debug("created builder: %s%p" FT_CRESET "\n", get_unique_col((U64)builder), builder);

	ft_memcpy(builder, pb, sizeof(struct s_program_builder));

	builder->headers_names = NULL;
	builder->headers_programs = NULL;
	builder->libraries = NULL;
	builder->programs = NULL;
	if (UNLIKELY((builder->headers_names = malloc(sizeof(string) * builder->headers_alloc)) == NULL) ||
		UNLIKELY((builder->headers_programs = malloc(sizeof(cl_program) * builder->headers_alloc)) == NULL) ||
		UNLIKELY((builder->libraries = malloc(sizeof(Library) * builder->libraries_alloc)) == NULL) ||
		UNLIKELY((builder->programs = malloc(sizeof(t_program) * builder->programs_alloc)) == NULL))
	{
		free(builder->headers_names);
		free(builder->headers_programs);
		free(builder->libraries);
		free(builder->programs);
		goto exit_omem;
	}


	for (U32 i = 0; i < builder->headers_n; i++)
		clfw_retain_program(builder->headers_programs[i]);
	for (U32 i = 0; i < builder->libraries_n; i++)
	{
		clfw_retain_program(builder->libraries[i].header);
		clfw_retain_program(builder->libraries[i].lib);
	}
	for (U32 i = 0; i < builder->programs_n; i++)
		clfw_retain_program(builder->programs[i].prog);

	return builder;

exit_omem:
	clc_error("program builder: out of memory\n");
	return NULL;
}

bool clc_builder_destroy(ProgramBuilder builder)
{
	ASSERT(builder != NULL, FALSE);

	clc_debug("destroying builder: %s%p" FT_CRESET "\n", get_unique_col((U64)builder), builder);
	for (U64 i = 0; i < builder->libraries_n; i++)
	{
		clfw_release_program(builder->libraries[i].lib);
		clfw_release_program(builder->libraries[i].header);
		free(builder->libraries[i].lib_name);
		free(builder->libraries[i].header_name);
	}
	for (U64 i = 0; i < builder->headers_n; i++)
	{
		clfw_release_program(builder->headers_programs[i]);
		free(builder->headers_names[i]);
	}
	for (U64 i = 0; i < builder->programs_n; i++)
		clfw_release_program(builder->programs[i].prog);

	free(builder->headers_names);
	free(builder->headers_programs);
	free(builder->programs);
	free(builder->libraries);
	free(builder);
	return TRUE;
}

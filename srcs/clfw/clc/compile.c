/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:03:35 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/12 03:48:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "libft/strings.h"
#include "libft/path.h"

static bool clc_begin(ProgramBuilder builder, enum e_program_type type)
{
	ASSERT(builder != NULL, FALSE)
	ASSERT(type == EXE || type == LIB, FALSE)

	builder->programs_n = 0;
	array_init(builder->programs, builder->programs_n, builder->programs_alloc,
			   return FALSE);
	builder->current_type = type;
	return TRUE;
}

bool clc_executable_begin(ProgramBuilder builder)
{
	return clc_begin(builder, EXE);
}

bool clc_library_begin(ProgramBuilder builder)
{
	return clc_begin(builder, LIB);
}

cl_program clc_end(ProgramBuilder builder)
{
	U64 progs_compiled_cnt;
	string build_log;
	cl_program out;

	ASSERT(builder != NULL, NULL)
	ASSERT(builder->programs_n != 0, NULL)
	ASSERT(builder->programs != NULL, NULL)
	ASSERT(builder->device != NULL, NULL)

	clc_info("begining compile and link sequence (%llu headers)\n", (LU64)builder->headers_n);
	{ /* compiling */
		progs_compiled_cnt = 0;
		for (U64 p = 0; p < builder->programs_n; p++)
		{
			if (builder->programs[p].compiled)
				/* program already compiled */
				continue;

			if (!clfw_compile_program(builder->programs[p].prog, 1, &builder->device->device_id, "-Werror",
									  builder->headers_n, builder->headers_programs, (const_string *)builder->headers_names, NULL, NULL))
			{
				clc_error("compilation failed\n");

				build_log = retrieve_build_log(builder, builder->programs[p].prog);
				if (build_log != NULL)
				{
					if (*build_log != '\0')
						clc_info("build log:\n%s\n", build_log);
					else
						clc_warn("no build log available\n");
				}
				free(build_log);
				return NULL;
			}

			builder->programs[p].compiled = TRUE;
			progs_compiled_cnt++;
		}

		clc_info("compiled %llu programs\n", (LU64)progs_compiled_cnt);
	}

	{						 /* linking */
		cl_program *to_link; /* buffer of programs to link */

		{ /* programs to link buffer init */
			if (UNLIKELY((to_link = malloc(sizeof(cl_program) * builder->programs_n)) == NULL))
				return NULL;
			for (U64 p = 0; p < builder->programs_n; p++)
				to_link[p] = builder->programs[p].prog;
		}

		if ((out = clfw_link_program(builder->device->ctx, 1, &builder->device->device_id, builder->current_type == LIB ? "-create-library -Werror" : " -Werror", builder->programs_n, to_link, NULL, NULL)) == NULL)
		{
			clc_error("linking failed\n");

			build_log = retrieve_build_log(builder, out);
			if (build_log != NULL)
			{
				if (*build_log != '\0')
					clc_info("build log:\n%s\n", build_log);
				else
					clc_warn("no build log available\n");
			}
			free(build_log);
		}
		else
			clc_info("linking successful\n");
		free(to_link);
	}

	for (U64 i = 0; i < builder->programs_n; i++)
		clfw_release_program(builder->programs[i].prog);
	free(builder->programs);
	builder->programs = NULL;
	builder->programs_alloc = 0;
	builder->programs_n = 0;

	return out;
}

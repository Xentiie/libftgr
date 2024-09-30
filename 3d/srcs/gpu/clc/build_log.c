/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:12:12 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 16:08:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"

string retrieve_build_log(ProgramBuilder builder, cl_program prog)
{
	S32 err;		   /* error value for opencl functions */
	string build_log;  /* build log */
	U64 build_log_len; /* build log length */

	{ /* retrieve build log length */
		err = clGetProgramBuildInfo(prog, builder->device, CL_PROGRAM_BUILD_LOG, 0, NULL, &build_log_len);
		if (err != 0)
		{
			clc_warn("couldn't retrieve build log: clGetProgramBuildInfo (1st invocation) returned %s(%d)\n", cl_error_lookup_table[-err], err);
			return NULL;
		}
	}

	{ /* initialize build log buffer */
		build_log = malloc(sizeof(U8) * (build_log_len + 1));
		if (UNLIKELY(build_log == NULL))
		{
			clc_error("couldn't retrieve build log: out of memory\n");
			return NULL;
		}
	}

	{ /* retrieve build log */
		err = clGetProgramBuildInfo(prog, builder->device, CL_PROGRAM_BUILD_LOG, build_log_len, build_log, NULL);
		if (err != 0)
		{
			free(build_log);
			clc_warn("couldn't retrieve build log: clGetProgramBuildInfo (2nd invocation)returned %s(%d)\n", cl_error_lookup_table[-err], err);
			return NULL;
		}
		build_log[build_log_len] = '\0';
	}

	return build_log;
}

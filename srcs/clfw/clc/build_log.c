/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:12:12 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 02:11:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"

string retrieve_build_log(ProgramBuilder builder, cl_program prog)
{
	ASSERT(builder != NULL, NULL)
	ASSERT(builder->device != NULL, NULL)

	string build_log;  /* build log */
	U64 build_log_len; /* build log length */

	{ /* retrieve build log length */
		if (!clfw_get_program_build_info(prog, builder->device->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &build_log_len))
		{
			clc_warn("couldn't retrieve build log\n");
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
		if (!clfw_get_program_build_info(prog, builder->device->device_id, CL_PROGRAM_BUILD_LOG, build_log_len, build_log, NULL))
		{
			free(build_log);
			clc_warn("couldn't retrieve build log\n");
			return NULL;
		}
		build_log[build_log_len] = '\0';
	}

	return build_log;
}

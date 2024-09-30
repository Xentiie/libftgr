/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_maths_cl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:33:35 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/29 00:25:36 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_maths_cl.h"
#include "libft/path.h"
#include "libft/strings.h"
#include "libft/io.h"

static string mkfilename(string dirname, string filename)
{
	static char file_paths[150];
	file_paths[ft_snprintf(file_paths, sizeof(file_paths) - 1, "%s%s", dirname, filename)] = '\0';
	return file_paths;
}

cl_program make_maths_cl(cl_device_id device, cl_context ctx, LibraryCache cache)
{
	// TODO: pas ouf
	string dirname = ft_path_dirname(__FILE__);

	ProgramBuilder builder = clc_builder_init(ctx, device);
	if (!clc_include_header(builder, mkfilename(dirname, "maths.cl.h")) ||
		!clc_library_begin(builder) ||
		!clc_ingest_file(builder, mkfilename(dirname, "lines.cl.c")) ||
		!clc_ingest_file(builder, mkfilename(dirname, "mat4x4.cl.c")) ||
		!clc_ingest_file(builder, mkfilename(dirname, "noise.cl.c")) ||
		!clc_ingest_file(builder, mkfilename(dirname, "rand_circle.cl.c")) ||
		!clc_ingest_file(builder, mkfilename(dirname, "rotate.cl.c")))
	{
		free(dirname);
		clc_builder_destroy(builder);
		return NULL;
	}

	free(dirname);
	cl_program lib = clc_end(builder);
	if (!clc_cache_lib(cache, builder, "maths.cl.h", lib))
	{
		clReleaseProgram(lib);
		lib = NULL;
	}
	clc_builder_destroy(builder);
	return lib;
}

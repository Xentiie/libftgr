/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:35:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/03 19:29:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(CLC_H)
#define CLC_H

#include "clfw/clfw.h"

#include "libft/types.h"
#include "libft/std.h"

/* interface to OpenCL's clCompileProgram and clLinkProgram */
typedef struct s_program_builder *ProgramBuilder;
/* caching mechanism for libraries */

typedef struct s_library
{
	cl_program header;
	string header_name;
	cl_program lib;
	string lib_name;
}	Library;

ProgramBuilder clc_builder_init(ClDevice device);
/* Duplicates builder `pb`, useful to avoid rebuilding the standard libraries */
ProgramBuilder clc_builder_init_from(ProgramBuilder pb);
bool clc_builder_destroy(ProgramBuilder builder);

bool clc_has_header(ProgramBuilder builder, const_string header_name);
bool clc_include_header(ProgramBuilder builder, const_string file_path);
bool clc_include_header_src(ProgramBuilder builder, const_string header_name, const_string src);
cl_program clc_header_get(ProgramBuilder builder, const_string header_name);

bool clc_executable_begin(ProgramBuilder builder);
bool clc_library_begin(ProgramBuilder builder);

bool clc_ingest_program(ProgramBuilder builder, cl_program program, bool compiled);
bool clc_ingest_file(ProgramBuilder builder, const_string path);
bool clc_ingest_str(ProgramBuilder builder, const_string str);
bool clc_ingest_library(ProgramBuilder builder, Library *library);

cl_program clc_end(ProgramBuilder builder);

bool clc_cache_lib(ProgramBuilder builder, const_string header_name, cl_program lib, const_string lib_name);
Library *clc_get_cached_lib(ProgramBuilder builder, string lib_name);

#endif
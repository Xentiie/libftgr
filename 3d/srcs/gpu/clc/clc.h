/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:35:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/03 03:30:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLC_H
#define CLC_H

#include "gpu/clfw/clfw.h"

#include "libft/types.h"
#include "libft/std.h"

/* interface to OpenCL's clCompileProgram and clLinkProgram */
typedef struct s_program_builder *ProgramBuilder;
/* caching mechanism for libraries */
typedef struct s_library_cache *LibraryCache;

ProgramBuilder clc_builder_init(ClDevice *device);
bool clc_builder_destroy(ProgramBuilder builder);

bool clc_include_header(ProgramBuilder builder, const_string file_path);

bool clc_executable_begin(ProgramBuilder builder);
bool clc_library_begin(ProgramBuilder builder);

bool clc_ingest_program(ProgramBuilder builder, cl_program program, bool compiled);
bool clc_ingest_file(ProgramBuilder builder, const_string path);
bool clc_ingest_str(ProgramBuilder builder, const_string str);
bool clc_ingest_library(ProgramBuilder builder, LibraryCache lib_cache, string lib_name);

cl_program clc_end(ProgramBuilder builder);

LibraryCache clc_cache_init();
bool clc_cache_lib(LibraryCache cache, ProgramBuilder builder, string header_name, cl_program lib);
/*
Uses any of *header_name, *header_prog or *lib to find a specific library.
Will return the ptr to the cached field used to find the library, and stores
the other fields in the corresponding arguments, if non-null
fields can be null to be ignored
*/
void *clc_get_lib(LibraryCache cache, cl_program *header_prog, cl_program *lib, string *header_name);

#endif
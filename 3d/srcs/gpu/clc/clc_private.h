/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clc_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:07:19 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/29 00:04:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLC_PRIVATE_H
#define CLC_PRIVATE_H

#include "clc.h"
#include "gpu/cl_errors/cl_errors.h"
#include "log/log.h"
#include "global.h"

#include "libft/std.h"
#include "libft/ansi.h"
#include "libft/macros.h"

#include <stdlib.h>
#include <stdio.h>

typedef enum e_program_type
{
	EXE,
	LIB,
} program_type;

typedef struct
{
	bool compiled;
	cl_program prog;
} program;

typedef struct s_program_builder
{
	cl_context ctx;
	cl_device_id device;

	program_type current_type;

	/* can be libraries */
	program *programs;
	U64 programs_n;
	U64 programs_alloc;

	string *headers_names;
	cl_program *headers_programs;
	U64 headers_n;
	U64 headers_alloc;
} *ProgramBuilder;

typedef struct s_library
{
	cl_program header;
	string header_name;
	cl_program lib;
}	t_library;

struct s_library_cache
{
	t_library *libraries;
	U64 libraries_n;
	U64 libraries_alloc;
};

#define clc_debug(...) log_debug("clc", __VA_ARGS__)
#define clc_info(...) log_info("clc", __VA_ARGS__)
#define clc_warn(...) log_warn("clc", __VA_ARGS__)
#define clc_error(...) log_error("clc", __VA_ARGS__)

string retrieve_build_log(ProgramBuilder builder, cl_program prog);
S32 _clc_add_header(ProgramBuilder builder, const_string header_name, cl_program header_prog);

void print_cl_prog(string txt, cl_program prog);

#endif
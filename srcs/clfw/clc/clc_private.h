/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clc_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:07:19 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 05:21:38 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLC_PRIVATE_H
#define CLC_PRIVATE_H

#include "clfw/clc.h"
#include "../clfw_private.h"
#include "log.h"

#include <stdlib.h>
#include <stdio.h>

#define header_src(name) name##_cl_h_source
#define file_src(name) name##_cl_c_source

extern char * header_src(clfw);
extern char * file_src(clfw);

extern char * header_src(maths);
extern char * file_src(bezier);
extern char * file_src(lines);
extern char * file_src(mat4x4);
extern char * file_src(noise);
extern char * file_src(rand_circle);
extern char * file_src(rotate);

enum e_program_type
{
	EXE,
	LIB,
};

typedef struct s_program
{
	bool compiled;
	cl_program prog;
} t_program;

typedef struct s_program_builder
{
	ClDevice *device;

	enum e_program_type current_type;

	Library *libraries;
	U64 libraries_n;
	U64 libraries_alloc;

	/* can be libraries */
	t_program *programs;
	U64 programs_n;
	U64 programs_alloc;

	string *headers_names;
	cl_program *headers_programs;
	U64 headers_n;
	U64 headers_alloc;
} *ProgramBuilder;

#define clc_tag "clc"
#define clc_debug(...) log_debug(clc_tag, __VA_ARGS__)
#define clc_info(...) log_info(clc_tag, __VA_ARGS__)
#define clc_warn(...) log_warn(clc_tag, __VA_ARGS__)
#define clc_error(...) log_error(clc_tag, __VA_ARGS__)

string retrieve_build_log(ProgramBuilder builder, cl_program prog);
bool _clc_add_header(ProgramBuilder builder, const_string header_name, cl_program header_prog);
string get_unique_col(U64 v);

#endif
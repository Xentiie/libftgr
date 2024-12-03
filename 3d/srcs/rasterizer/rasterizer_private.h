/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer_private.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:59:21 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/12 03:54:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_PRIVATE_H
#define PIPELINE_PRIVATE_H

#include "rasterizer.h"

#define rast_tag "rast"
#define rast_debug(...) log_debug(rast_tag, __VA_ARGS__)
#define rast_info(...) log_info(rast_tag, __VA_ARGS__)
#define rast_warn(...) log_warn(rast_tag, __VA_ARGS__)
#define rast_error(...) log_error(rast_tag, __VA_ARGS__)

typedef struct s_pipeline {
	ClDevice device;

	cl_program shader_prog;
	cl_kernel vert_shdr;
	cl_kernel frgm_shdr;

	U32 vert_stride;

	//TODO: double buffering ?
	U32 verts_buffer_alloc;
	cl_mem verts_buffer;

	U32 tris_cnt;
	U32 tris_buffer_alloc;
	cl_mem tris_buffer;

	U32 interphase_buffer_alloc;
	cl_mem interphase_buffer;

	cl_mem atm_subtris;

	/* dirty = a cl_mem has been reallocated, so we need to call clfw_set_kernel_arg again */
	bool dirty;

} *Pipeline;

bool pipeline_set_arg(Pipeline pipe);

#endif
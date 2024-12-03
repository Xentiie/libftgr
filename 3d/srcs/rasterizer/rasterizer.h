/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:59:03 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/12 03:54:47 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
#define PIPELINE_H

#define CL_NO_PROTOTYPES
#include "clfw/clc.h"
#include "3dfw/3dfw.h"

typedef struct s_pipeline *Pipeline;

/* initializes a new pipeline */
Pipeline pipeline_init(ClDevice device);
void pipeline_free(Pipeline pipe);
/*
Begins a ProgramBuilder, which already includes the maths.cl library, and the tris_setup kernel.
`cache` should contain the maths.cl library.
User should not call clc_executable_begin/clc_end
User should provide source code for a `vertex_shader` function prototyped like so:
t_v4 vertex_shader(global U8 *p, t_mat4x4 model_to_world, t_mat4x4 world_to_clip);
*/
ProgramBuilder pipeline_shader_builder(Pipeline pipe, ProgramBuilder builder);
/*
Link both vertex and fragment shaders
*/
bool pipeline_link_shader(Pipeline pipe, ProgramBuilder builder);

/*
Initializes internal buffers. `tris_count_hint` is an optional hint of the max amount of triangles rendered. If 0, a default
value of 2000 is set.
*/
bool pipeline_buffers_init(Pipeline pipe, U64 tris_count_hint);
void pipeline_set_vertex_stride(Pipeline pipe, U32 stride);
bool pipeline_fill_verts(Pipeline pipe, void *buffer, U32 count);
/* Should be an array of t_iv3 */
bool pipeline_fill_tris(Pipeline pipe, void *buffer, U32 count);

bool pipeline_set_arg(Pipeline pipe);
bool pipeline_prepare(Pipeline pipe);

void pipeline_execute(Pipeline pipe, struct s_object object, struct s_camera cam);

#endif
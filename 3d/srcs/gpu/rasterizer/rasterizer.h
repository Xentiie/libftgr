/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:07:55 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/04 09:16:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_RASTERIZER_H
#define CL_RASTERIZER_H

#include "gpu/clc/clc.h"
#include "gpu/cl_errors/cl_errors.h"
/*
//TODO:
faut faire un truc propre ici, parce que mes shaders ont besoin de la lib maths cl
donc faudra trouver un moyen de passer ca proprement, mais j'aimerais bien eviter de
refaire une grosse structure qui garde tout en mémoire
pour le moment je passe le cache des lib en arguments, faudra changer
*/
ProgramBuilder vertex_shader_begin(ClDevice *device, LibraryCache cache);
cl_kernel vertex_shader_end(ProgramBuilder builder, cl_program *out_program);

struct s_3d_object {
	struct s_object obj;
	void *vertex_buffer;
	cl_mem *cl_vertex_buffer;
	U8 vbo_stride;
};

struct s_vertex_shader {
	cl_kernel shader;
	cl_mem atm_subtris;
};

void render_mesh_gpu(
	cl_kernel vertex_shader,
	ClDevice *device,
	struct s_object object,
	struct s_camera cam);

#endif
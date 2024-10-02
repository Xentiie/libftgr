/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:07:55 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 14:39:25 by reclaire         ###   ########.fr       */
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
ProgramBuilder vertex_shader_begin(cl_context ctx, cl_device_id device, LibraryCache cache);
cl_kernel vertex_shader_end(ProgramBuilder builder, cl_program *out_program);

void render_mesh_gpu(
	cl_kernel vertex_shader,
	cl_context ctx, cl_command_queue queue,
	struct s_object object,
	struct s_camera cam);

#endif
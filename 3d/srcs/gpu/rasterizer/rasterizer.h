/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:07:55 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 09:15:40 by reclaire         ###   ########.fr       */
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

void ft3d_draw_lines(
	cl_kernel vertex_shader,
	cl_context ctx, cl_command_queue queue,
	t_v3 *points, U64 points_cnt, t_iv2 *indices, U64 indices_cnt,
	struct s_camera cam);

#endif
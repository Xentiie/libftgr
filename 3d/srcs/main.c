/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:27:08 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/07 01:33:25 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

int main()
{

	F32 fov = 90.0f;
	F32 near = 0.01f;
	F32 far = 1000.0f;
	t_mat4x4 proj_mat = ft_matrix_perspective(fov, near, far);

	t_mat4x4 world_mat = (t_mat4x4){
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	F32 verts[] = {
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f};

	U32 triangles[] = {
		// Front face
		0, 1, 2, 2, 3, 0,
		// Back face
		4, 5, 6, 6, 7, 4,
		// Left face
		0, 3, 7, 7, 4, 0,
		// Right face
		1, 5, 6, 6, 2, 1,
		// Top face
		3, 2, 6, 6, 7, 3,
		// Bottom face
		0, 1, 5, 5, 4, 0};

	t_ftgr_ctx *ctx = ftgr_create_ctx();
	t_ftgr_win *win = ftgr_new_window(ctx, ivec2(200, 200), "3D");

	while (ftgr_poll(ctx))
	{
		ftgr_display_fps(win);
		
		t_v4 tris = ft_matrix_mult_v4(proj_mat, vec4(verts[triangles[0]], verts[triangles[1]], verts[triangles[2]], 1));
		t_v4 tris_projected = vec4_scl(tris, tris.w);
		t_v3 tris_screen = vec3();
		
	}
}

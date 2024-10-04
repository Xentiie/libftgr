/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:33:52 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/04 08:46:37 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "3dfw/3dfw.h"

const t_v3 cube_verts[] = {
	{-1.0f, -1.0f, -1.0f},
	{-1.0f, 1.0f, -1.0f},
	{1.0f, 1.0f, -1.0f},
	{1.0f, -1.0f, -1.0f},
	{1.0f, 1.0f, 1.0f},
	{1.0f, -1.0f, 1.0f},
	{-1.0f, 1.0f, 1.0f},
	{-1.0f, -1.0f, 1.0f}
};
const t_iv3 cube_tris[] = {
	//south
	{0, 1, 2},
	{0, 2, 3},

	//east
	{3, 2, 4},
	{3, 4, 5},

	//north
	{5, 4, 6},
	{5, 6, 7},

	//west
	{7, 6, 1},
	{7, 1, 0},

	//top
	{1, 6, 4},
	{1, 4, 2},

	//bottom
	{5, 7, 0},
	{5, 0, 3}
};

const t_v3 cube_verts_old[] = {
	{-1.0f, -1.0f, -1.0f},
	{1.0f, -1.0f, -1.0f},
	{1.0f, 1.0f, -1.0f},
	{-1.0f, 1.0f, -1.0f},
	{-1.0f, -1.0f, 1.0f},
	{1.0f, -1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f},
	{-1.0f, 1.0f, 1.0f}};

const t_iv3 cube_tris_old[] = {
	// Front face
	{2, 1, 0},
	{0, 3, 2},
	// Back face
	{4, 5, 6},
	{6, 7, 4},
	// Left face
	{0, 3, 7},
	{7, 4, 0},
	// Right face
	{1, 5, 6},
	{6, 2, 1},
	// Top face
	{3, 2, 6},
	{6, 7, 3},
	// Bottom face
	{0, 1, 5},
	{5, 4, 0}};

struct s_object cube = {
	.col = COL_GRAY,
	.verts = (t_v3 *)cube_verts,
	.verts_cnt = array_len(cube_verts),
	.tris = ((t_iv3 *)cube_tris),
	.tris_cnt = array_len(cube_tris),
	//.tris_cnt = 1,

	.wireframe = TRUE,
	.render = FALSE};
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tris_setup.cl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:34:53 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/03 11:06:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.cl.h"

t_v4 vertex_shader(global U8 *p, t_mat4x4 model_to_world, t_mat4x4 world_to_clip);

__kernel void vertex_main(
	global U8 *verts, U32 verts_stride,
	global S32 *tris, U32 tris_cnt,
	global t_v4 *out_stream,
	U32 out_stream_size,
	global S32 *atm_out_stream_n,
	t_iv4 cam_pos,
	t_mat4x4 model_to_world,
	t_mat4x4 world_to_clip)
{
	S32 id = get_global_id(0);
	if (id >= tris_cnt)
		return;

	//t_iv3 tri = ivec3(
	//	*(((U8 *)tris) + ((id * 3) + 1) * sizeof(S32)),
	//	*(((U8 *)tris) + ((id * 3) + 2) * sizeof(S32)),
	//	*(((U8 *)tris) + ((id * 3) + 3) * sizeof(S32)));

	t_iv3 tri = *(global t_iv3 *)(tris + (id * 3));
	t_iv3 ofs = tri * (int3)(verts_stride);

	t_v4 p1 = vertex_shader(verts + ofs.x, model_to_world, world_to_clip);
	t_v4 p2 = vertex_shader(verts + ofs.y, model_to_world, world_to_clip);
	t_v4 p3 = vertex_shader(verts + ofs.z, model_to_world, world_to_clip);

	t_v4 normal = normalize(cross(p2 - p1, p3 - p1));
	if (dot(normal.xyz, p1.xyz - convert_float3(cam_pos.xyz)) > 0)
		return;

	S32 n_tris = 1; //Number of triangles generated
	S32 i = atomic_add(atm_out_stream_n, n_tris); //Allocate space in the output buffer
	if (i >= out_stream_size) //No more space -> stop
		return;

	t_v3 rcpW = vec3(rcp(p1.w), rcp(p2.w), rcp(p3.w));
	p1 *= rcpW.x;
	p2 *= rcpW.y;
	p3 *= rcpW.z;
	p1.w = rcpW.x;
	p2.w = rcpW.y;
	p3.w = rcpW.z;

	out_stream[tri.x] = p1;
	out_stream[tri.y] = p2;
	out_stream[tri.z] = p3;
}
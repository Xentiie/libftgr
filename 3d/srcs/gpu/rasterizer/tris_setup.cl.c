/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tris_setup.cl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:34:53 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/09 15:19:51 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.cl.h"

t_v4 vertex_shader(U8 *p, t_mat4x4 model_to_world, t_mat4x4 world_to_clip);

void draw_normals(global S32 *atm_subtris, global t_v4 *out_stream, U32 out_stream_size, global U8 *verts, t_iv3 ofs, t_mat4x4 model_to_world, t_mat4x4 world_to_clip)
{
	S32 i = atomic_inc(atm_subtris); // Allocate space in the output buffer
	if (i >= out_stream_size)		 // No more space -> stop
		return;

	t_v4 wp1 = vertex_shader(verts + ofs.x, model_to_world, ft_mat4x4_identity);
	t_v4 wp2 = vertex_shader(verts + ofs.y, model_to_world, ft_mat4x4_identity);
	t_v4 wp3 = vertex_shader(verts + ofs.z, model_to_world, ft_mat4x4_identity);

	t_v3 normal = normalize(cross(wp2.xyz - wp1.xyz, wp3.xyz - wp1.xyz));
	t_v4 center = (wp1 + wp2 + wp3) / 3.0f;
	t_v3 norm_p = center.xyz + normal * 0.2f;

	out_stream[i * 3 + 0] = vertex_shader((U8 *)&center, ft_mat4x4_identity, world_to_clip);
	out_stream[i * 3 + 1] = vertex_shader((U8 *)&norm_p, ft_mat4x4_identity, world_to_clip);
	out_stream[i * 3 + 2] = vertex_shader((U8 *)&norm_p, ft_mat4x4_identity, world_to_clip);

	out_stream[i * 3 + 0].x /= out_stream[i * 3 + 0].w;
	out_stream[i * 3 + 0].y /= out_stream[i * 3 + 0].w;

	out_stream[i * 3 + 1].x /= out_stream[i * 3 + 1].w;
	out_stream[i * 3 + 1].y /= out_stream[i * 3 + 1].w;

	out_stream[i * 3 + 2].x /= out_stream[i * 3 + 2].w;
	out_stream[i * 3 + 2].y /= out_stream[i * 3 + 2].w;
}

__kernel void tris_setup(
	global U8 *verts, U32 verts_stride,
	global S32 *tris, U32 tris_cnt,
	global t_v4 *out_stream,
	U32 out_stream_size,
	global U32 *atm_subtris,
	t_v3 cam_pos,
	t_mat4x4 model_to_world,
	t_mat4x4 world_to_clip,
	global t_v4 *debug)
{
	S32 id;			 /* Thread id */
	t_iv3 tri;		 /* Current triangle vertex indices */
	t_iv3 ofs;		 /* Offset in verts buffer for triangle vertices */
	t_v4 p1, p2, p3; /* Clip space triangle coordinates */
	t_v3 normal;	 /* Triangle's normal vector */
	U8 n_tris;		 /* Number of triangles generated */
	S32 out_index;	 /* index in the output buffer for generated tris */

	id = get_global_id(0);
	if (id >= tris_cnt)
		return;

	tri = ivec3(
		*(((global U8 *)tris) + ((id * 3) + 0) * sizeof(S32)),
		*(((global U8 *)tris) + ((id * 3) + 1) * sizeof(S32)),
		*(((global U8 *)tris) + ((id * 3) + 2) * sizeof(S32)));

	ofs = tri * (int3)(verts_stride);

	p1 = vertex_shader(verts + ofs.x, model_to_world, world_to_clip);
	p2 = vertex_shader(verts + ofs.y, model_to_world, world_to_clip);
	p3 = vertex_shader(verts + ofs.z, model_to_world, world_to_clip);

	normal = normalize(cross(p2.xyz - p1.xyz, p3.xyz - p1.xyz));
	if (dot(normal, p1.xyz) > 0.0f)
		return;

#ifdef DRAW_NORMALS
	draw_normals(atm_subtris, out_stream, out_stream_size, verts, ofs, model_to_world, world_to_clip);
#endif

	n_tris = 1;									 /* Number of triangles generated */
	out_index = atomic_add(atm_subtris, n_tris); /* Allocate space in the output buffer */
	if (out_index >= out_stream_size)			 /* No more space -> stop */
		return;

	t_v3 rcpW = vec3(rcp(p1.w), rcp(p2.w), rcp(p3.w));
	p1 *= rcpW.x;
	p2 *= rcpW.y;
	p3 *= rcpW.z;
	p1.w = rcpW.x;
	p2.w = rcpW.y;
	p3.w = rcpW.z;

	out_stream[out_index * 3 + 0] = p1;
	out_stream[out_index * 3 + 1] = p2;
	out_stream[out_index * 3 + 2] = p3;
}
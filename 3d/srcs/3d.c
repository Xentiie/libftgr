/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:25:15 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/19 16:42:19 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "3d.h"
#include "libft/ansi.h"

t_v4 get_plane_eq(t_v3 p1, t_v3 p2, t_v3 p3)
{
	t_v3 v1;
	t_v3 v2;
	t_v3 n;
	F32 k;

	v1 = vec3_sub(p2, p1);
	v2 = vec3_sub(p3, p1);
	n = vec3_scl(ft_normalize3(ft_cross3(v1, v2)), -1);
	k = -ft_dot3(p1, n);
	return vec4(n.x, n.y, n.z, k);
}

t_v4 world_to_screen(struct s_camera cam, t_v3 point)
{
	t_mat4x4 world_to_clip = cam_get_world_to_clip(cam);
	t_v4 screen_point = ft_mat4x4_mult_v4(world_to_clip, vec4(point.x, point.y, point.z, 1.f));

	F32 rcpW = 1.0f / screen_point.w;

	screen_point.x = floorf((screen_point.x * rcpW + 1.0f) / 2.0f * cam.surface->size.x);
	screen_point.y = floorf((screen_point.y * rcpW + 1.0f) / 2.0f * cam.surface->size.y);

	return vec4(screen_point.x, screen_point.y, screen_point.z, screen_point.w);
}

t_v3 screen_to_world(struct s_camera cam, t_v2 point)
{
	t_mat4x4 clip_to_view = ft_mat4x4_invert(cam_get_cam_to_clip(cam));
	t_mat4x4 view_to_world = ft_mat4x4_invert(cam_get_world_to_cam(cam));

	point.x = (point.x / (F32)cam.surface->size.x * 2.0f) - 1.0f;
	point.y = (point.y / (F32)cam.surface->size.y * 2.0f) - 1.0f;

	t_v4 view_point = ft_mat4x4_mult_v4(clip_to_view, vec4(point.x, point.y, 0.0f, 1.0f));
	view_point.w = 1.f / view_point.w;
	view_point.x /= view_point.w;
	view_point.y /= view_point.w;
	view_point.z /= view_point.w;
	t_v4 world_point4 = ft_mat4x4_mult_v4(view_to_world, view_point);

	t_v3 world_point = vec3(world_point4.x, world_point4.y, world_point4.z);
	//world_point = vec3_add(world_point, vec3_scl(cam.forward, cam.near));

	return world_point;
}

bool clip_line_with_plane(t_v3 plane_n, t_v3 plane_pos, t_v3 p1, t_v3 p2, t_v3 *out_intersect)
{
	t_v3 l = vec3_sub(p2, p1);
	F32 dot = ft_dot3(l, plane_n);
	if (dot == .0f)
		return FALSE;

	t_v3 l_to_plane = vec3_sub(plane_pos, p1);
	F32 t = ft_dot3(l_to_plane, plane_n) / dot;

	out_intersect->x = p1.x + t * l.x;
	out_intersect->y = p1.y + t * l.y;
	out_intersect->z = p1.z + t * l.z;
	return TRUE;
}

void setcol(t_ftgr_img *img, t_iv2 xy, t_v3 w, void *data)
{
	U8 *ptr = data;

	t_ftgr_img *depth_buffer = *(t_ftgr_img **)ptr;
	ptr += sizeof(void *);
	t_v4 p1 = *(t_v4 *)ptr;
	ptr += sizeof(t_v4);
	t_v4 p2 = *(t_v4 *)ptr;
	ptr += sizeof(t_v4);
	t_v4 p3 = *(t_v4 *)ptr;
	ptr += sizeof(t_v4);

	t_v2 t1 = {0, 0};
	t_v2 t2 = {1, 0};
	t_v2 t3 = {1, 1};

	t_v2 uv;
	uv.x = w.x * t1.x + w.y * t2.x + w.z * t3.x;
	uv.y = w.x * t1.y + w.y * t2.y + w.z * t3.y;
	uv.y = 1 - uv.y;

	F32 depth = ((w.x * p1.w) + (w.y * p2.w) + (w.z * p3.w));

	// z = p1.z;
	if (*(F32 *)ftgr_get_pixel_addr(depth_buffer, xy.x, xy.y) < depth)
	{
		*(F32 *)ftgr_get_pixel_addr(depth_buffer, xy.x, xy.y) = depth;
		*(U32 *)ftgr_get_pixel_addr(img, xy.x, xy.y) = ftgr_color_to_int((t_color){uv.x * 255.0f, uv.y * 255.0f, 0, 255});
		//*(U32 *)ftgr_get_pixel_addr(img, xy.x, xy.y) = ftgr_color_to_int((t_color){depth * 25, depth * 25, depth * 25, 255});
	}
}

void render_model(struct s_camera cam, struct s_object obj)
{
	t_mat4x4 world_to_clip = cam_get_world_to_clip(cam);
	t_mat4x4 model_to_world = object_get_model_to_world(obj);
	t_v3 *verts = obj.verts;
	U64 verts_cnt = obj.verts_cnt;
	t_iv3 *tris = obj.tris;
	U64 tris_cnt = obj.tris_cnt;

	if (obj.wireframe)
	{
		for (U64 i = 0; i < obj.tris_cnt; i++)
		{
			t_iv3 id = tris[i];
			t_v4 p1 = ft_mat4x4_mult_v4(model_to_world, vec4(verts[id.x].x, verts[id.x].y, verts[id.x].z, 1.f));
			t_v4 p2 = ft_mat4x4_mult_v4(model_to_world, vec4(verts[id.y].x, verts[id.y].y, verts[id.y].z, 1.f));
			t_v4 p3 = ft_mat4x4_mult_v4(model_to_world, vec4(verts[id.z].x, verts[id.z].y, verts[id.z].z, 1.f));
			draw_3d_line(cam, vec3(p1.x, p1.y, p1.z), vec3(p2.x, p2.y, p2.z), COL_WHITE, TRUE);
			draw_3d_line(cam, vec3(p2.x, p2.y, p2.z), vec3(p3.x, p3.y, p3.z), COL_WHITE, TRUE);
			draw_3d_line(cam, vec3(p3.x, p3.y, p3.z), vec3(p1.x, p1.y, p1.z), COL_WHITE, TRUE);
		}
	}

	if (obj.render)
	{
		t_v4 *clip_space_verts = malloc(sizeof(t_v4) * verts_cnt);
		for (U64 i = 0; i < verts_cnt; i++)
		{
			t_v4 world_pos = ft_mat4x4_mult_v4(model_to_world, vec4(verts[i].x, verts[i].y, verts[i].z, 1.f));
			clip_space_verts[i] = ft_mat4x4_mult_v4(world_to_clip, world_pos);
			if (clip_space_verts[i].w != 0)
			{
				clip_space_verts[i].x /= clip_space_verts[i].w;
				clip_space_verts[i].y /= clip_space_verts[i].w;
			}
			clip_space_verts[i].x *= cam.surface->size.x / 2.f;
			clip_space_verts[i].y *= cam.surface->size.y / 2.f;
		}

		for (U64 i = 0; i < obj.tris_cnt; i++)
		{
			t_iv3 id = tris[i];
			t_v4 p1 = clip_space_verts[id.x];
			t_v4 p2 = clip_space_verts[id.y];
			t_v4 p3 = clip_space_verts[id.z];

			struct
			{
				void *ptr;
				t_v4 p1;
				t_v4 p2;
				t_v4 p3;
			} data = {.ptr = cam.depth_buffer, .p1 = p1, .p2 = p2, .p3 = p3};
			ftgr_fill_triangle_e(cam.surface, ivec2(p1.x, p1.y), ivec2(p2.x, p2.y), ivec2(p3.x, p3.y), setcol, &data);
		}

		free(clip_space_verts);
	}
}

static void _draw_3d_line(t_ftgr_img *img, t_iv2 xy, t_iv4 lp1lp2, void *data)
{
	U8 *ptr = data;

	t_ftgr_img *depth_buffer = *(t_ftgr_img **)ptr;
	ptr += sizeof(void *);
	t_v4 p1 = *(t_v4 *)ptr;
	ptr += sizeof(t_v4);
	t_v4 p2 = *(t_v4 *)ptr;
	ptr += sizeof(t_v4);
	t_color col = *(t_color *)ptr;

	F32 t = ft_fmax(ft_invlerp(lp1lp2.x, lp1lp2.z, xy.x), ft_invlerp(lp1lp2.y, lp1lp2.w, xy.y));
	F32 w = -ft_lerp(p1.w, p2.w, t);

	if (*(F32 *)ftgr_get_pixel_addr(depth_buffer, xy.x, xy.y) < w)
	{
		*(F32 *)ftgr_get_pixel_addr(depth_buffer, xy.x, xy.y) = w;
		*(U32 *)ftgr_get_pixel_addr(img, xy.x, xy.y) = ftgr_color_to_int(col);
		//*(U32 *)ftgr_get_pixel_addr(img, xy.x, xy.y) = ftgr_color_to_int((t_color){w * 25, w * 25, w * 25, 255});
	}
}
void draw_3d_line(struct s_camera cam, t_v3 lp1, t_v3 lp2, t_color col, bool depth)
{
	if (!clip_line_with_cam(cam, &lp1, &lp2))
		return;

	t_v4 p1 = world_to_screen(cam, lp1);
	t_v4 p2 = world_to_screen(cam, lp2);

	if (depth)
	{

		struct
		{
			t_ftgr_img *depth_buffer;
			t_v4 p1;
			t_v4 p2;
			t_color col;
		} data = {
			.p1 = p1,
			.p2 = p2,
			.depth_buffer = cam.depth_buffer,
			.col = col};
		ftgr_draw_line_e(cam.surface, ivec2(p1.x, p1.y), ivec2(p2.x, p2.y), _draw_3d_line, &data);
	}
	else
		ftgr_draw_line(cam.surface, ivec2(p1.x, p1.y), ivec2(p2.x, p2.y), col);
}

void draw_frustum(struct s_camera cam, t_v3 c1[4], t_v3 c2[4], t_color col)
{
	draw_3d_line(cam, c1[0], c1[1], col, TRUE);
	draw_3d_line(cam, c1[1], c1[2], col, TRUE);
	draw_3d_line(cam, c1[2], c1[3], col, TRUE);
	draw_3d_line(cam, c1[3], c1[0], col, TRUE);

	draw_3d_line(cam, c2[0], c2[1], col, TRUE);
	draw_3d_line(cam, c2[1], c2[2], col, TRUE);
	draw_3d_line(cam, c2[2], c2[3], col, TRUE);
	draw_3d_line(cam, c2[3], c2[0], col, TRUE);

	draw_3d_line(cam, c1[0], c2[0], col, TRUE);
	draw_3d_line(cam, c1[1], c2[1], col, TRUE);
	draw_3d_line(cam, c1[2], c2[2], col, TRUE);
	draw_3d_line(cam, c1[3], c2[3], col, TRUE);
}

void draw_camera(struct s_camera cam, struct s_camera target)
{
	t_v4 screen_pos = world_to_screen(cam, target.pos);
	ftgr_draw_disc(cam.surface, ivec2(screen_pos.x, screen_pos.y), 5, COL_RED);
	draw_3d_line(cam, target.pos, vec3_add(target.pos, vec3_scl(target.forward, 5)), COL_LIGHT_RED, TRUE);
	draw_3d_line(cam, target.pos, vec3_add(target.pos, vec3_scl(target.up, 0.5f)), COL_LIGHT_RED, TRUE);

	t_v3 near[4];
	t_v3 far[4];
	cam_get_frustum(target, near, far);
	draw_frustum(cam, near, far, COL_DARK_GREEN);
}

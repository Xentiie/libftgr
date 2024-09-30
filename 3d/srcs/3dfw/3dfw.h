/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3dfw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:02:07 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 12:20:16 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _3DFW_H
#define _3DFW_H

#include "libftgr.h"
#include "libft/lists.h"
#include "global.h"

struct s_object {
	t_v3 pos;
	t_v3 rot;
	t_v3 scl;

	t_v3 *verts;
	U64 verts_cnt;
	t_iv3 *tris;
	U64 tris_cnt;

	bool wireframe;
	bool render;
	t_color col;
};

struct s_camera {
	t_v3 pos;
	t_v3 forward;
	t_v3 up;

	F32 near;
	F32 far;
	F32 fov;

	t_ftgr_img *surface;
	t_ftgr_img *depth_buffer;
};

bool cam_init_depth_buffer(struct s_camera *cam);
t_mat4x4 cam_get_cam_to_clip(struct s_camera cam);
t_mat4x4 cam_get_orientation(struct s_camera cam);
t_mat4x4 cam_get_world_to_cam(struct s_camera cam);
t_mat4x4 cam_get_cam_to_world(struct s_camera cam);
t_mat4x4 cam_get_world_to_clip(struct s_camera cam);
void cam_get_frustum(struct s_camera cam, t_v3 near[4], t_v3 far[4]);

t_v4 world_to_screen(struct s_camera cam, t_v3 point);
t_v3 screen_to_world(struct s_camera cam, t_v2 point);
t_v3 view_to_world(struct s_camera cam, t_v2 point);

t_mat4x4 object_get_model_to_world(struct s_object obj);

void render_model(struct s_camera cam, struct s_object obj);

void draw_3d_line(struct s_camera cam, t_v3 lp1, t_v3 lp2, t_color col, bool depth);
void draw_frustum(struct s_camera cam, t_v3 c1[4], t_v3 c2[4], t_color col);
void draw_grid(struct s_camera cam, t_v3 grid_pos, t_v3 grid_up);
void draw_camera(struct s_camera cam, struct s_camera target);

t_v4 get_plane_eq(t_v3 p1, t_v3 p2, t_v3 p3);
bool clip_line_with_plane(t_v3 plane_n, t_v3 plane_pos, t_v3 p1, t_v3 p2, t_v3 *out_intersect);
bool clip_line_with_cam(struct s_camera cam, t_v3 *p1, t_v3 *p2);

t_widget *new_info_line(t_list **lines, t_bitmap *bitmap, string label, string (*get_value_str)(void *), string (*dump_value_str)(void *), void *ptr);

void print_mat(string name, t_mat4x4 mat);

#endif
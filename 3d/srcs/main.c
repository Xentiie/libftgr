/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:27:08 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 13:32:53 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libftgr.h"
#include "libft/io.h"
#include "libft/ansi.h"
#include "libft/limits.h"
#include "libft/path.h"

#include "3dfw/3dfw.h"
#include "infolines/infolines.h"
#include "gpu/clc/clc.h"
#include "gpu/maths.cl/make_maths_cl.h"
#include "gpu/cl_init/cl_init.h"
#include "gpu/rasterizer/rasterizer.h"

#include "infolines_getters.h"

void camera_move(t_ftgr_ctx *ctx, struct s_camera *cam);

const t_v3 cube_verts[] = {
	{-1.0f, -1.0f, -1.0f},
	{1.0f, -1.0f, -1.0f},
	{1.0f, 1.0f, -1.0f},
	{-1.0f, 1.0f, -1.0f},
	{-1.0f, -1.0f, 1.0f},
	{1.0f, -1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f},
	{-1.0f, 1.0f, 1.0f}};

const t_iv3 cube_tris[] = {
	// Front face
	{0, 1, 2},
	{2, 3, 0},
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
	.tris = (t_iv3 *)cube_tris,
	.tris_cnt = array_len(cube_tris),

	.wireframe = TRUE,
	.render = FALSE};

t_ftgr_ctx *ctx;
t_ftgr_win *win;

void draw_debug_scene(struct s_camera cam)
{
	F32 dtime = ftgr_delta_time(ctx);
	(void)dtime;
	struct s_camera cam2;
	cam2.depth_buffer = cam.depth_buffer;
	cam2.surface = cam.surface;
	cam2.near = 1.f;
	cam2.far = 10.f;
	cam2.fov = 30.f;
	cam2.pos = vec3(0, 0, 0);
	cam2.up = vec3(0, 1, 0);
	cam2.forward = vec3(-1, 0, 0);

	cube.pos = vec3_add(cam2.pos, vec3_scl(cam2.forward, ft_lerp(cam2.near, cam2.far, 0.5f)));

	bool cam2_view = ftgr_is_key_pressed(ctx, 'r');

	if (!cam2_view)
	{
		draw_camera(cam, cam2);
		t_v2 near_plane_size, far_plane_size;
		t_v3 near_center, far_center;

		F32 aspect_ratio = (F32)cam2.surface->size.x / (F32)cam2.surface->size.y;

		near_plane_size.y = 2 * tanf(ft_radians(cam2.fov) / 2.0f) * cam2.near;
		near_plane_size.x = near_plane_size.y * aspect_ratio;

		far_plane_size.y = 2 * tanf(ft_radians(cam2.fov) / 2.0f) * cam2.far;
		far_plane_size.x = far_plane_size.y * aspect_ratio;

		near_center = vec3_add(cam2.pos, vec3_scl(ft_normalize3(cam2.forward), cam2.near));
		far_center = vec3_add(cam2.pos, vec3_scl(ft_normalize3(cam2.forward), cam2.far));

		t_v4 near_center_screen = world_to_screen(cam, near_center);
		t_v4 far_center_screen = world_to_screen(cam, far_center);
		ftgr_draw_disc(cam.surface, ivec2(near_center_screen.x, near_center_screen.y), 3, COL_GREEN);
		ftgr_draw_disc(cam.surface, ivec2(far_center_screen.x, far_center_screen.y), 3, COL_GREEN);

		{ /* mouse dir */
			t_iv2 mouse_pos = ftgr_mouse_get_pos(ctx, win);
			t_v3 p = screen_to_world(cam2, ivec2_flt(mouse_pos));
			t_v3 p_dir = ft_normalize3(vec3_sub(p, cam2.pos));
			t_v4 p2 = world_to_screen(cam, p);
			ftgr_draw_disc(cam.surface, ivec2(p2.x, p2.y), 5, COL_BLUE);
			draw_3d_line(cam, cam2.pos, vec3_add(cam2.pos, vec3_scl(p_dir, 5)), COL_LIGHT_GREEN, TRUE);
		}
	}
	render_model(cam2_view ? cam2 : cam, cube);
}

int main()
{
	t_list *info_lines;		/* info lines list */
	t_bitmap bitmap;		/* default bitmap */
	t_ftgr_img *bitmap_img; /* image for default bitmap */
	struct s_camera cam;	/* main camera */

	{ /* general init */
		ctx = ftgr_create_ctx();
		win = ftgr_new_window(ctx, ivec2(1024, 512), "3D");

		{ /* bitmap init */
			bitmap_img = ftgr_load_png(ctx, "./font_bitmap_white.png");
			ftgr_init_bitmap(&bitmap, bitmap_img, ivec2(5, 7), 18, ivec2(2, 2));
		}

		{ /* cam init */
			cam.pos = vec3(12.86, 3.31, 7.14);
			cam.forward = vec3(-0.92, -0.14, -0.37);
			cam.up = vec3(-0.12, 0.99, -0.09);
			cam.near = .1f;
			cam.far = 90.0f;
			cam.fov = 70.0f;
			cam.surface = win->surface;
			cam.depth_buffer = malloc(sizeof(t_ftgr_img));
			cam_init_depth_buffer(&cam);
		}

		{ /* cube init */
			cube.rot = vec3(0, 37, 0);
			cube.scl = vec3(0.5, 0.5, 0.5);
		}

		{ /* info lines */
			info_lines = NULL;
			t_widget *il;

			/* Cube infos */
			il = new_info_line(&info_lines, &bitmap, "Cube", get_cube_str, NULL, &cube);
			ftgr_add_widget(il, win->w_root);

			/* Active camera infos */
			il = new_info_line(&info_lines, &bitmap, "Camera", get_cam_str, dump_cam_str, &cam);
			ftgr_add_widget(il, win->w_root);

			/* Active camera infos */
			il = new_info_line(&info_lines, &bitmap, "Fps", get_fps_str, NULL, ctx);
			ftgr_add_widget(il, win->w_root);
		}
	}

	cl_platform_id platform = NULL;
	cl_device_id device = NULL;
	cl_context cl_ctx = NULL;
	cl_command_queue queue = NULL;

	if (!cl_init(&platform, &device, &cl_ctx, &queue))
		return 1;

	LibraryCache libcache = clc_cache_init();
	if (!libcache)
		return 1;
	if (!make_maths_cl(device, cl_ctx, libcache))
		return 1;

	cl_kernel vertex_shader;
	{
		ProgramBuilder vertex_builder = vertex_shader_begin(cl_ctx, device, libcache);
		if (!clc_ingest_file(vertex_builder, "srcs/simple_vertex_shader.cl.c"))
			return 1;
		vertex_shader = vertex_shader_end(vertex_builder, NULL);
	}

	t_v3 points[] = {
		{0, 0, 0},
		{10, 0, 0},
		{10, 10, 0}};
	t_iv2 indices[] = {
		{0, 1},
		{1, 2}};

	while (ftgr_poll(ctx))
	{
		cam.surface = win->surface;
		ft_bzero(cam.surface->data, cam.surface->data_size);
		/*
		//TODO:
		pq je me fais chier a utiliser -cam.far ?
		parce que actuellement le depth buffer contient des valeurs allant de 0 a -cam.far (-cam.far étant le plus éloigné)
		ca serait cool de pouvoir just bzero le truc
		*/
		for (U64 i = 0; i < cam.depth_buffer->data_size; i += cam.depth_buffer->bpp)
			*(F32 *)(cam.depth_buffer->data + i) = -cam.far;

		camera_move(ctx, &cam);

		ft3d_draw_lines(vertex_shader, cl_ctx, queue, points, array_len(points), indices, array_len(indices), cam);
		draw_debug_scene(cam);
		ftgr_handle_widget_events(win, win->w_root);
		ftgr_draw_widget_recursive(win->surface, win->w_root);
		ftgr_swap_buffers(win);
		ftgr_display_fps(win);
	}
}

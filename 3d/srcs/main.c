/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:27:08 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/18 21:17:08 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libftgr.h"
#include "./3d.h"
#include "libft/io.h"
#include "libft/ansi.h"
#include "libft/limits.h"
#undef near
#undef far

static string get_float_str(void *ptr);
static string get_cube_str(void *ptr);
static string get_cam_str(void *ptr);
static string dump_cam_str(void *ptr);
static string get_fps_str(void *ptr);

F32 _fov = 30.0f;
F32 _near = 1.f;
F32 _far = 10.0f;

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
	.verts = cube_verts,
	.verts_cnt = array_len(cube_verts),
	.tris = cube_tris,
	.tris_cnt = array_len(cube_tris),

	.wireframe = TRUE,
	.render = FALSE};

t_ftgr_ctx *ctx;
t_ftgr_win *win;

void draw_debug_scene(struct s_camera cam)
{
	static t_v3 cube_pos = {0, 0, 0};

	F32 dtime = ftgr_delta_time(ctx);
	struct s_object cube2;
	struct s_camera cam2;
	cam2.depth_buffer = cam.depth_buffer;
	cam2.surface = cam.surface;

	cam2.near = _near;
	cam2.far = _far;
	cam2.fov = _fov;
	cam2.pos = vec3(0, 0, 0);
	cam2.up = vec3(0, 1, 0);
	cam2.forward = vec3(-1, 0, 0);

	cube2 = cube;
	cube2.pos = vec3_add(cube_pos, vec3_add(cam2.pos, vec3_scl(cam2.forward, ft_lerp(cam2.near, cam2.far, 0.5f))));
	cube2.tris_cnt = 1;

	if (ftgr_is_key_pressed(ctx, 'v'))
	{
		if (ftgr_is_key_pressed(ctx, 'q'))
			cube_pos.z -= dtime;
		if (ftgr_is_key_pressed(ctx, 'd'))
			cube_pos.z += dtime;
		if (ftgr_is_key_pressed(ctx, 's'))
			cube_pos.y -= dtime;
		if (ftgr_is_key_pressed(ctx, 'z'))
			cube_pos.y += dtime;
	}

	if (ftgr_is_key_pressed(ctx, 'n'))
	{
		if (ftgr_is_key_pressed(ctx, 'w'))
			_near -= dtime;
		if (ftgr_is_key_pressed(ctx, 'x'))
			_near += dtime;
	}
	if (ftgr_is_key_pressed(ctx, 'f'))
	{
		if (ftgr_is_key_pressed(ctx, 'w'))
			_far -= dtime * 2;
		if (ftgr_is_key_pressed(ctx, 'x'))
			_far += dtime * 2;
	}
	if (ftgr_is_key_pressed(ctx, 'o'))
	{
		if (ftgr_is_key_pressed(ctx, 'w'))
			_fov -= dtime * 2;
		if (ftgr_is_key_pressed(ctx, 'x'))
			_fov += dtime * 2;
	}

	bool cam2_view = ftgr_is_key_pressed(ctx, 'r');

	if (!cam2_view)
	{
		draw_camera(cam, cam2);
		t_v3 cam_right = ft_normalize3(ft_cross3(cam2.forward, cam2.up));
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
	}
	render_model(cam2_view ? cam2 : cam, cube2);

	t_v3 p = screen_to_world(cam2, vec2(0, 0));
	t_v4 p2 = world_to_screen(cam, p);
	ftgr_draw_disc(cam.surface, ivec2(p2.x, p2.y), 5, COL_BLUE);

	t_mat4x4 m1 = cam_get_world_to_view(cam);
	t_mat4x4 m2 = ft_mat4x4_invert(m1);

	t_mat4x4 m3 = ft_mat4x4_mult_mat(m1, m2);
	t_mat4x4 m4 = ft_mat4x4_mult_mat(m2, m1);
	print_mat("m3", m3);
	print_mat("m4", m4);

	t_v4 _p1 = ft_mat4x4_mult_v4(m1, vec4(10, 20, 30, 0));
	t_v4 _p2 = ft_mat4x4_mult_v4(m2, _p1);

	printf("%f %f %f %f\n", _p1.x, _p1.y, _p1.z, _p1.w);
	printf("%f %f %f %f\n\n", _p2.x, _p2.y, _p2.z, _p2.w);
}

int main()
{
	t_list *info_lines = NULL;
	ctx = ftgr_create_ctx();
	win = ftgr_new_window(ctx, ivec2(1024, 512), "3D");
	t_ftgr_img *bitmap_img = ftgr_load_png(ctx, "./font_bitmap_white.png");
	t_bitmap bitmap;
	ftgr_init_bitmap(&bitmap, bitmap_img, ivec2(5, 7), 18, ivec2(2, 2));

	struct s_camera cam;
	cam.pos = vec3(12.86, 3.31, 7.14);
	cam.forward = vec3(-0.92, -0.14, -0.37);
	cam.up = vec3(-0.12, 0.99, -0.09);

	F32 *depth_buffer = malloc(sizeof(F32) * win->surface->size.x * win->surface->size.y);

	cam.near = .1f;
	cam.far = 90.0f;
	cam.fov = 100.0f;
	cam.surface = win->surface;
	cam.depth_buffer = &(t_ftgr_img){
		.bpp = sizeof(F32),
		.data = (U8 *)depth_buffer,
		.line_size = sizeof(F32) * cam.surface->size.x,
		.data_size = sizeof(F32) * cam.surface->size.x * cam.surface->size.y,
		.size = cam.surface->size};

	cube.pos = vec3(-4.28, -0.34, -0.27);
	cube.rot = vec3(0, 37, 0);
	cube.scl = vec3(0.5, 0.5, 0.5);

	{ /* Info lines */
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

		/* near plane */
		il = new_info_line(&info_lines, &bitmap, "Near", get_float_str, NULL, &_near);
		ftgr_add_widget(il, win->w_root);
		/* far plane */
		il = new_info_line(&info_lines, &bitmap, "Far", get_float_str, NULL, &_far);
		ftgr_add_widget(il, win->w_root);
		/* fov */
		il = new_info_line(&info_lines, &bitmap, "Fov", get_float_str, NULL, &_fov);
		ftgr_add_widget(il, win->w_root);
	}

	while (ftgr_poll(ctx))
	{
		cam.surface = win->surface;
		ft_bzero(cam.surface->data, cam.surface->data_size);
		for (U64 i = 0; i < cam.depth_buffer->data_size; i += cam.depth_buffer->bpp)
			*(F32 *)(cam.depth_buffer->data + i) = -cam.far;

		F32 dtime = ftgr_delta_time(ctx);
		F32 time = ftgr_time(ctx);

		t_v3 cam_right;
		if (!ftgr_is_key_pressed(ctx, 'v'))
		{ /* camera movement */
			t_v3 move = vec3(0, 0, 0);
			move.x = ftgr_is_key_pressed(ctx, 'z') - ftgr_is_key_pressed(ctx, 's');
			move.y = ftgr_is_key_pressed(ctx, ' ') - ftgr_is_key_pressed(ctx, 'c');
			move.z = ftgr_is_key_pressed(ctx, 'd') - ftgr_is_key_pressed(ctx, 'q');
			bool sprint = ftgr_mouse_pressed(ctx, MOUSE_LEFT);

			cam_right = ft_normalize3(ft_cross3(cam.forward, cam.up));
			cam.pos = vec3_add(cam.pos, vec3_scl(cam.forward, move.x * dtime * 10 * (sprint ? 8 : 1)));
			cam.pos = vec3_add(cam.pos, vec3_scl(cam.up, move.y * dtime * 10 * (sprint ? 8 : 1)));
			cam.pos = vec3_add(cam.pos, vec3_scl(cam_right, move.z * dtime * 10 * (sprint ? 8 : 1)));
		}

		{ /* camera rotation */
			t_mat4x4 camera_orientation;
			t_v3 rotate = vec3(0, 0, 0);

			if (ftgr_is_key_pressed(ctx, 'j'))
				rotate.x -= dtime * 0.5f;
			if (ftgr_is_key_pressed(ctx, 'l'))
				rotate.x += dtime * 0.5f;
			if (ftgr_is_key_pressed(ctx, 'k'))
				rotate.y -= dtime * 0.5f;
			if (ftgr_is_key_pressed(ctx, 'i'))
				rotate.y += dtime * 0.5f;

			if (rotate.x != 0.0f || rotate.y != 0.0f || rotate.z != 0.0f)
				camera_orientation = cam_get_camera_orientation(cam);

			if (rotate.x != 0.0f || rotate.y != 0.0f)
			{
				t_v3 c0 = *(t_v3 *)ft_mat4x4_col(&camera_orientation, 0);
				t_v3 c1 = *(t_v3 *)ft_mat4x4_col(&camera_orientation, 1);
				t_v3 c2 = *(t_v3 *)ft_mat4x4_col(&camera_orientation, 2);

				t_v3 tmp = vec3_sub(vec3_scl(c2, cosf(rotate.x)), vec3_scl(c0, sinf(rotate.x)));

				cam.forward = ft_normalize3(vec3_sub(vec3_scl(c1, sinf(rotate.y)), vec3_scl(tmp, cosf(rotate.y))));
				cam.up = ft_normalize3(vec3_add(vec3_scl(c1, cosf(rotate.y)), vec3_scl(tmp, sinf(rotate.y))));
			}

			if (rotate.z != 0.0f)
			{
				t_v4 up4 = ft_mat4x4_mult_v4(ft_mat4x4_transpose(camera_orientation), vec4(cam.up.x, cam.up.y, cam.up.z, 1.0f));
				t_v4 tmp = ft_mat4x4_mult_v4(camera_orientation, vec4(up4.x * cos(rotate.z) - sin(rotate.z), up4.x * sin(rotate.z) + up4.y * cos(rotate.z), up4.z, 1.0f));
				cam.up = vec3(tmp.x, tmp.y, tmp.z);
			}
		}

		// draw_cube_scene(cam);
		// draw_line_intersect_plane_scene(cam);
		draw_debug_scene(cam);

		ftgr_handle_widget_events(win, win->w_root);
		ftgr_draw_widget_recursive(win->surface, win->w_root);
		ftgr_swap_buffers(win);
		ftgr_display_fps(win);
	}
}

#pragma region Info lines funcs

static string get_float_str(void *ptr)
{
	static char buf[10];
	buf[snprintf(buf, sizeof(buf) - 1, "%f", *(F32 *)ptr)] = '\0';
	return buf;
}

static string get_cube_str(void *ptr)
{
	static char buf[100];
	struct s_object *cube = (struct s_object *)ptr;
	buf[snprintf(buf, sizeof(buf) - 1, "pos:{%.2f %.2f %.2f} rot:{%.2f %.2f %.2f}",
				 cube->pos.x, cube->pos.y, cube->pos.z,
				 cube->rot.x, cube->rot.y, cube->rot.z)] = '\0';
	return buf;
}

static string get_cam_str(void *ptr)
{
	static char buf[100];
	struct s_camera *cam = (struct s_camera *)ptr;
	buf[snprintf(buf, sizeof(buf) - 1, "pos:{%.2f %.2f %.2f} forward:{%.2f %.2f %.2f} up:{%.2f %.2f %.2f}",
				 cam->pos.x, cam->pos.y, cam->pos.z,
				 cam->forward.x, cam->forward.y, cam->forward.z,
				 cam->up.x, cam->up.y, cam->up.z)] = '\0';
	return buf;
}

static string dump_cam_str(void *ptr)
{
	static char buf[200];
	struct s_camera *cam = (struct s_camera *)ptr;
	buf[snprintf(buf, sizeof(buf) - 1, "cam.pos = vec3(%.2f, %.2f, %.2f);\ncam.forward = vec3(%.2f, %.2f, %.2f);\ncam.up = vec3(%.2f, %.2f, %.2f);",
				 cam->pos.x, cam->pos.y, cam->pos.z,
				 cam->forward.x, cam->forward.y, cam->forward.z,
				 cam->up.x, cam->up.y, cam->up.z)] = '\0';
	return buf;
}

static string get_fps_str(void *ptr)
{
	static char buf[10];
	buf[snprintf(buf, sizeof(buf) - 1, "%f", 1.0f / ftgr_delta_time((t_ftgr_ctx *)ptr))] = '\0';
	return buf;
}
#pragma endregion
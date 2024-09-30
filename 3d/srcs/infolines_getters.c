/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infolines_getters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:19:36 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 12:32:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "3dfw/3dfw.h"
#include <stdio.h>

string get_float_str(void *ptr)
{
	static char buf[10];
	buf[snprintf(buf, sizeof(buf) - 1, "%f", *(F32 *)ptr)] = '\0';
	return buf;
}

string get_cube_str(void *ptr)
{
	static char buf[100];
	struct s_object *cube = (struct s_object *)ptr;
	buf[snprintf(buf, sizeof(buf) - 1, "pos:{%.2f %.2f %.2f} rot:{%.2f %.2f %.2f}",
				 cube->pos.x, cube->pos.y, cube->pos.z,
				 cube->rot.x, cube->rot.y, cube->rot.z)] = '\0';
	return buf;
}

string get_cam_str(void *ptr)
{
	static char buf[100];
	struct s_camera *cam = (struct s_camera *)ptr;
	buf[snprintf(buf, sizeof(buf) - 1, "pos:{%.2f %.2f %.2f} forward:{%.2f %.2f %.2f} up:{%.2f %.2f %.2f}",
				 cam->pos.x, cam->pos.y, cam->pos.z,
				 cam->forward.x, cam->forward.y, cam->forward.z,
				 cam->up.x, cam->up.y, cam->up.z)] = '\0';
	return buf;
}

string dump_cam_str(void *ptr)
{
	static char buf[200];
	struct s_camera *cam = (struct s_camera *)ptr;
	buf[snprintf(buf, sizeof(buf) - 1, "cam.pos = vec3(%.2f, %.2f, %.2f);\ncam.forward = vec3(%.2f, %.2f, %.2f);\ncam.up = vec3(%.2f, %.2f, %.2f);",
				 cam->pos.x, cam->pos.y, cam->pos.z,
				 cam->forward.x, cam->forward.y, cam->forward.z,
				 cam->up.x, cam->up.y, cam->up.z)] = '\0';
	return buf;
}

string get_fps_str(void *ptr)
{
	static char buf[10];
	buf[snprintf(buf, sizeof(buf) - 1, "%f", 1.0f / ftgr_delta_time((t_ftgr_ctx *)ptr))] = '\0';
	return buf;
}
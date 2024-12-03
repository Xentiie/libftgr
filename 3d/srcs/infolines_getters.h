/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infolines_getters.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:22:12 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 01:16:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFOLINES_GETTERS_H
#define INFOLINES_GETTERS_H

#include "libft/std.h"

string get_float_str(void *ptr);
string get_cube_str(void *ptr);
string get_cam_str(void *ptr);
string dump_cam_str(void *ptr);
string get_fps_str(void *ptr);

#endif
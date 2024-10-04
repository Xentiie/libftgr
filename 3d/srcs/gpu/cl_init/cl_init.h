/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:54:12 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 18:08:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_INIT_H
#define CL_INIT_H

#include "libft/types.h"
#define CL_TARGET_OPENCL_VERSION 300
#include "CL/cl.h"

bool cl_init(cl_platform_id *o_platform, cl_device_id *o_device, cl_context *o_ctx, cl_command_queue *o_queue);

#endif
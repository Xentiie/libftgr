/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:23:02 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 18:27:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_init.h"
#include "gpu/cl_errors/cl_errors.h"
#include "log/log.h"
#include "global.h"

#include <stdio.h>

bool cl_init(cl_platform_id *o_platform, cl_device_id *o_device, cl_context *o_ctx, cl_command_queue *o_queue)
{
	S32 err;
	cl_platform_id platform;
	cl_device_id device;
	cl_context ctx;
	cl_command_queue queue;

	{ /* select platform */
		if (o_platform == NULL || *o_platform == NULL)
		{
			U32 n_platforms;
			cl_platform_id platforms[10];
			err = clGetPlatformIDs(array_len(platforms), platforms, &n_platforms);
			CHK_CLCALL(return FALSE);
			if (n_platforms == 0)
			{
				log_error("cl init", "no platforms detected\n");
				return FALSE;
			}
			platform = platforms[0];
		}
		else
			platform = *o_platform;

		{ /* print platform name */
			char platform_name[32];
			err = clGetPlatformInfo(platform, CL_PLATFORM_NAME, sizeof(platform_name) - 1, platform_name, NULL);
			CHK_CLCALL(return FALSE);
			platform_name[sizeof(platform_name) - 1] = '\0';
			log_info("cl init", "used platform: %s\n", platform_name);
		}
	}

	{ /* select device */
		if (o_device == NULL || *o_device == NULL)
		{
			cl_device_id devices[10];
			U32 n_devices;

			err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, array_len(devices), devices, &n_devices);
			CHK_CLCALL(return FALSE);

			if (n_devices == 0)
			{
				log_error("cl init", "no devices detected\n");
				return FALSE;
			}
			device = devices[0];
		}
		else
			device = *o_device;

		{ /* print device name */
			char device_name[32];
			err = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_name) - 1, device_name, NULL);
			CHK_CLCALL(return FALSE);
			device_name[sizeof(device_name) - 1] = '\0';
			log_info("cl init", "used device: %s\n", device_name);
		}
	}

	{ /* context */
		ctx = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
		CHK_CLCALL(return FALSE);
	}

	{ /* command queue */
		queue = clCreateCommandQueueWithProperties(ctx, device, NULL, &err);
		CHK_CLCALL(return FALSE);
	}

	if (o_platform)
		*o_platform = platform;
	if (o_device)
		*o_device = device;
	if (o_ctx)
		*o_ctx = ctx;
	if (o_queue)
		*o_queue = queue;

	return TRUE;
}

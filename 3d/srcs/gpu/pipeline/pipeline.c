/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:03:40 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 17:23:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline_private.h"

Pipeline new_pipeline(cl_device_id device, cl_context ctx, cl_command_queue queue)
{
	Pipeline pipe = malloc(sizeof(Pipeline));
	pipe->device = device;
	pipe->ctx = ctx;
	pipe->queue = queue;

	pipe->vertshdr_builder = clc_builder_init(ctx, device);
	pipe->fragshdr_builder = clc_builder_init(ctx, device);

	clc_include_header(pipe->vertshdr_builder, "./srcs/opencl_renderer");

	return pipe;
}

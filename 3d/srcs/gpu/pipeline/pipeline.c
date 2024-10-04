/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:03:40 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/04 09:58:59 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline_private.h"

Pipeline new_pipeline(ClDevice *device)
{
	Pipeline pipe = malloc(sizeof(struct s_pipeline));
	pipe->device = device->device_id;
	pipe->ctx = device->ctx;
	pipe->queue = device->queue;

	pipe->vertshdr_builder = clc_builder_init(device);
	pipe->fragshdr_builder = clc_builder_init(device);

	clc_include_header(pipe->vertshdr_builder, "./srcs/opencl_renderer");

	return pipe;
}

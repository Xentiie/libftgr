/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:59:21 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/04 09:58:42 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_PRIVATE_H
#define PIPELINE_PRIVATE_H

#include "pipeline.h"

typedef struct s_pipeline {
	cl_context ctx;
	cl_device_id device;
	cl_command_queue queue;

	ProgramBuilder vertshdr_builder;
	ProgramBuilder fragshdr_builder;
} *Pipeline;

#endif
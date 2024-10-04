/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:59:03 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 18:27:58 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
#define PIPELINE_H

#define CL_TARGET_OPENCL_VERSION 300
#include "CL/cl.h"
#include "gpu/clc/clc.h"

typedef struct s_pipeline *Pipeline;

#endif
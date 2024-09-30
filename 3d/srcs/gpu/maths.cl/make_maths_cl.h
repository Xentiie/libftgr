/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_maths_cl.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:40:49 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 18:12:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_MATHS_H
#define CL_MATHS_H

#include "gpu/clc/clc.h"

cl_program make_maths_cl(cl_device_id device, cl_context ctx, LibraryCache cache);

#endif
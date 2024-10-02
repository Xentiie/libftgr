/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clc.cl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:29:58 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 14:31:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLC_CL_H
#define CLC_CL_H

#ifndef __OPENCL_VERSION__
#define global
#define local
#define private
#define constant
#endif

#define uniform(x) constant x

#endif
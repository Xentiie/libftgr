/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clfw_private.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:03:32 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/02 03:00:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLFW_PRIVATE_H
#define CLFW_PRIVATE_H

#include "clfw_wrapper_generated.h"
#include "libft/std.h"
#include "clfw.h"
#include "log/log.h"

extern S32 clfw_last_call;
extern S32 clfw_last_error;
extern const_string clfw_func_calls[];

#define clfw_tag "clfw"
#define clfw_error(...) log_error(clfw_tag, __VA_ARGS__)
#define clfw_warn(...) log_warn(clfw_tag, __VA_ARGS__)
#define clfw_info(...) log_info(clfw_tag, __VA_ARGS__)
#define clfw_debug(...) log_debug(clfw_tag, __VA_ARGS__)

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:46:50 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/08 04:25:01 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include "libft/std.h"

#define array_len(x) (sizeof(x) / sizeof((x)[0]))

void print_mat(string name, t_mat4x4 mat);

#endif
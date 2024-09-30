/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:48:26 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 17:49:55 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_ERRORS_H
#define CL_ERRORS_H

#include "libft/types.h"
#include "libft/macros.h"
#include "log/log.h"

extern const_string cl_error_lookup_table[];

#define CHK_CLCALL(exit)                                                                                                       \
	if (UNLIKELY(err != 0))                                                                                                    \
	{                                                                                                                          \
		log_error("cl call", "%d:%s\n", err, cl_error_lookup_table[-err]);                                                                                                           \
		FT_DEPAREN(exit);                                                                                                      \
	}

#endif
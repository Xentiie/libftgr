/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:07:32 by reclaire          #+#    #+#             */
<<<<<<<< HEAD:srcs/log/log.h
/*   Updated: 2024/12/03 03:32:56 by reclaire         ###   ########.fr       */
========
/*   Updated: 2024/10/11 01:17:07 by reclaire         ###   ########.fr       */
>>>>>>>> 3357d0c81fa52b9d081e13212418880d6cbadb44:include/log.h
/*                                                                            */
/* ************************************************************************** */

#if !defined(LOG_H)
#define LOG_H

<<<<<<<< HEAD:srcs/log/log.h
#include "libft/libft.h"
========
#include "libft/std.h"
>>>>>>>> 3357d0c81fa52b9d081e13212418880d6cbadb44:include/log.h
#include "libft/io.h"
#include "libft/debug.h"

enum e_log_level
{
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
};

extern enum e_log_level log_level;
extern bool log_timestamps;

#define log_debug(tag, ...) (log_debug)(FT_IFDEBUG(__FILE__, __LINE__, ) tag, __VA_ARGS__)
#define log_info(tag, ...) (log_info)(FT_IFDEBUG(__FILE__, __LINE__, ) tag, __VA_ARGS__)
#define log_warn(tag, ...) (log_warn)(FT_IFDEBUG(__FILE__, __LINE__, ) tag, __VA_ARGS__)
#define log_error(tag, ...) (log_error)(FT_IFDEBUG(__FILE__, __LINE__, ) tag, __VA_ARGS__)

void (log_debug)(FT_IFDEBUG(const_string file, S32 line, ) const_string tag, string fmt, ...);
void (log_info)(FT_IFDEBUG(const_string file, S32 line, ) const_string tag, string fmt, ...);
void (log_warn)(FT_IFDEBUG(const_string file, S32 line, ) const_string tag, string fmt, ...);
void (log_error)(FT_IFDEBUG(const_string file, S32 line, ) const_string tag, string fmt, ...);

#define ASSERT(cond, ret) if (UNLIKELY(!(cond))) { log_error("ASSERT", "assertion failed: (%s) is FALSE\n", #cond); return ret; }

#endif
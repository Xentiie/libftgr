/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:07:32 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/03 19:28:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LOG_H)
#define LOG_H

#include "libft/libft.h"
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
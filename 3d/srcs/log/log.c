/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:07:41 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/02 19:03:09 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "libft/std.h"
#include "libft/ansi.h"
#include "libft/path.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

enum e_log_level log_level = LOG_DEBUG;
bool log_timestamps = TRUE;

static string log_type_str[][2] = {
	{"debug", FT_BOLD FT_FOREGROUND_COLOR(160, 160, 160)},
	{"info", FT_BOLD FT_FOREGROUND_COLOR(200, 255, 200)},
	{"warn", FT_BOLD FT_FOREGROUND_COLOR(255, 230, 0)},
	{"error", FT_BOLD FT_FOREGROUND_COLOR(255, 50, 0)}};

static void _log(const_string file, S32 line, enum e_log_level level, string tag, string fmt, va_list l)
{
	FILE *f;

	if (log_level > level)
		return;
	f = level == LOG_ERROR ? stderr : stdout;
	if (log_level == LOG_DEBUG)
	{
		string filename = ft_path_filename(file);
		string dirname = ft_path_dirname(file);
		string dir_up = ft_path_filename(dirname);
		fprintf(f, FT_FOREGROUND_COLOR(127, 127, 127) "[%s%s:%d]" FT_CRESET, dir_up, filename, line);
		free(filename);
		free(dirname);
		free(dir_up);
	}
	fprintf(f, "[%s%s" FT_CRESET "]" FT_CRESET, log_type_str[level][1], log_type_str[level][0]);
	if (tag)
		fprintf(f, FT_FOREGROUND_COLOR(255, 127, 255) "[%s] " FT_CRESET, tag);
	vfprintf(f, fmt, l);
}

#define mk_log_f(fname, type)                                      \
	void fname(const_string file, S32 line, string tag, string fmt, ...) \
	{                                                              \
		va_list l;                                                 \
		va_start(l, fmt);                                          \
		_log(file, line, type, tag, fmt, l);                       \
		va_end(l);                                                 \
	}

mk_log_f((log_debug), LOG_DEBUG);
mk_log_f((log_info), LOG_INFO);
mk_log_f((log_warn), LOG_WARN);
mk_log_f((log_error), LOG_ERROR);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:07:41 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/03 03:40:52 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "libft/std.h"
#include "libft/ansi.h"
#include "libft/paths.h"

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

static void _log(FT_IFDEBUG(const_string file, S32 line, ) enum e_log_level level, const_string tag, string fmt, va_list l)
{
	t_file *f;

	if (log_level > level)
		return;
	f = level == LOG_ERROR ? ft_fstderr : ft_fstdout;
	if (log_level == LOG_DEBUG)
	{
		FT_IFDEBUG(
			string filename = ft_path_filename(file);
			string dirname = ft_path_dirname(file);
			string dir_up = ft_path_filename(dirname);
			ft_fprintf(f, FT_FOREGROUND_COLOR(127, 127, 127) "[%s%s:%d]" FT_CRESET, dir_up, filename, line);
			free(filename);
			free(dirname);
			free(dir_up);)
	}
	ft_fprintf(f, "[%s%s" FT_CRESET "]" FT_CRESET, log_type_str[level][1], log_type_str[level][0]);
	if (tag)
		ft_fprintf(f, FT_FOREGROUND_COLOR(255, 127, 255) "[%s] " FT_CRESET, tag);
	ft_vfprintf(f, fmt, l);
}

#define mk_log_f(fname, type)                                                               \
	void fname(FT_IFDEBUG(const_string file, S32 line, ) const_string tag, string fmt, ...) \
	{                                                                                       \
		va_list l;                                                                          \
		va_start(l, fmt);                                                                   \
		_log(FT_IFDEBUG(file, line, ) type, tag, fmt, l);                                   \
		va_end(l);                                                                          \
	}

mk_log_f((log_debug), LOG_DEBUG);
mk_log_f((log_info), LOG_INFO);
mk_log_f((log_warn), LOG_WARN);
mk_log_f((log_error), LOG_ERROR);

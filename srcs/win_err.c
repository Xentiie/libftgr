/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:15:32 by reclaire          #+#    #+#             */
/*   Updated: 2024/02/02 23:15:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "libftgr_win_int.h"

#ifdef FT_OS_WIN

#define PRINT_ERROR(name, error_code, msg) ft_fprintf(ft_fstderr, "(%s:%d) [" name ":%d] %s\n", file, line, error_code, msg)
#define PRINT_ERROR2(name, error_code, msg, ...) ft_fprintf(ft_fstderr, "(%s:%d) [" name ":%d]" msg "\n", file, line, error_code, __VA_ARGS__)
#define PRINT_ERROR_WIN(error_code, msg) PRINT_ERROR("WIN", error_code, msg)
#define PRINT_ERROR_FT(error_code, msg) PRINT_ERROR("FT", error_code, msg)

void(_ftgr_error)(string file, S32 line)
{
	DWORD err = GetLastError();
	if (err != 0)
	{
		string buffer = NULL;
		size_t size = FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&buffer,
			0,
			NULL);

		for (ssize_t i = size - 1; i >= 0; i--)
		{
			if (buffer[i] == '\n')
			{
				buffer[i] = '\0';
				break;
			}
		}
		PRINT_ERROR_WIN((S32)err, buffer);
		LocalFree(buffer);
	}
	else if (ft_errno != FT_OK)
		PRINT_ERROR_FT(ft_errno, ft_strerror(ft_errno));
	else
		PRINT_ERROR2("UNKNOWN", -1, "Unknown error (%lu)", err);
}

#endif
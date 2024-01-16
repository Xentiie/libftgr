/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftwin32_int.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 23:21:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 12:05:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTWIN32_INT_H
# define LIBFTWIN32_INT_H

# include <windows.h>
# include "libft.h"


# ifndef FT_LISTS
#  error Ftwin32 requires FT_LISTS to be defined
# endif
# ifndef FT_MATHS
#  error Ftwin32 requires FT_MATHS to be defined
# endif
# ifndef FT_HASHMAPS
#  error Ftwin32 requires FT_HASHMAPS to be defined
# endif


# define FTWIN32_WINDOW_CLASS "FtMainWindowClass"
# define FTWIN32_PROP_NAME L"FTWIN32"

typedef t_error_code (*t_loop_hook)();

typedef struct s_ftwin32_ctx {
	
    HINSTANCE	instance_handle;
    ATOM		main_window_class;

	t_list			*windows;
	t_list			*loop_hooks;

	bool			run;

}	t_ftwin32_ctx;

typedef struct s_ftwin32_win {
    
	t_ftwin32_ctx	*ctx;
    HWND			window_handle;

}   t_ftwin32_win;

#define	FTWIN32_WINDOW(lst) ((t_ftwin32_win*)(lst->content))

#endif
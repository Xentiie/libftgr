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
# include "../libftgr_constants.h"


# ifndef FT_LISTS
#  error Ftwin32 requires FT_LISTS to be defined
# endif
# ifndef FT_MATHS
#  error Ftwin32 requires FT_MATHS to be defined
# endif


# define FTWIN32_WINDOW_CLASS "FtMainWindowClass"
# define FTWIN32_PROP_NAME L"FTWIN32"

typedef S32 (*t_loop_hook)();

typedef struct s_ftwin32_ctx {
	
    HINSTANCE	instance_handle;
    ATOM		main_window_class;

	t_list		*windows;
	t_list		*loop_hooks;

	bool		run;

	void		(*error_callback)();
	void		(*on_quit)();
}	t_ftwin32_ctx;

typedef struct s_ftwin32_win {
    
	t_ftwin32_ctx	*ctx;
    HWND			window_handle;
	S32				cursor_mode;
}   t_ftwin32_win;

#define	FTWIN32_WINDOW(lst) ((t_ftwin32_win*)(lst->content))

t_ftwin32_ctx   *ftwin32_create_ctx();

void ftwin32_loop(t_ftwin32_ctx *ctx);

t_ftwin32_win *ftwin32_new_window(t_ftwin32_ctx *ctx, t_iv2 size, const_string title);
void ftwin32_free_window(t_ftwin32_win *win);

void ftwin32_set_quit_handler(t_ftwin32_ctx *ctx, void (*handler)());
void ftwin32_quit(t_ftwin32_ctx *ctx);

void _ftwin32_error(t_ftwin32_ctx *ctx);

#endif
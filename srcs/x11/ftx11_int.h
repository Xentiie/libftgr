/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx11_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:46:17 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/10 10:53:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTX11_INT_H
# define FTX11_INT_H

# include "libft.h"

# ifndef FT_LISTS
#  error Ftx11 requires FT_LISTS to be defined
# endif
# ifndef FT_MATHS
#  error Ftx11 requires FT_MATHS to be defined
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/mman.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/extensions/XShm.h>
# include <X11/XKBlib.h>

typedef t_error_code (*t_loop_hook)();

typedef struct s_ftx11_ctx {
	
	Display		*display;
	Window		root;
	Colormap	cmap;
	Visual		*visual;

	S32				screen;
	S32				depth;

	Atom			del_win_atom;
	Atom			protocols_atom;

	bool			flush;
	bool			use_xshm;
	bool			run;

	S32				pixmap_shm_format;

	t_list		*windows;
	t_list		*loop_hooks;
}	t_ftx11_ctx;

#define	FTX11_WINDOW(lst) ((t_ftx11_win*)(lst->content))
#define	FTX11_LOOP_HOOK(lst) ((t_loop_hook)(lst->content))
typedef struct s_ftx11_win {
	Window	window;
	GC			gc;
}	t_ftx11_win;

U32	_ftx11_keysym2uni(U32 keysym);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftwin32_free_window.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:33:07 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/16 23:33:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftwin32_int.h"

static bool _find_win(void *w1, void *w2)
{
	return w1 == w2;
}

void ftwin32_free_window(t_ftwin32_win *win)
{
	if (win->window_handle)
	{
		BOOL ret = DestroyWindow(win->window_handle);
		//Ne pas changer, documentation dis que on doit check explicitement pour TRUE/FALSE
		if (ret == FALSE)
			_ftwin32_error(win->ctx);
		if (ret == TRUE)
			win->window_handle = NULL;
	}
	
	t_list *lst = ft_lstfind(win->ctx->windows, _find_win, win);
	if (lst)
	{
		ft_lstremove(&win->ctx->windows, lst, NULL);
	}

	free(win);
}

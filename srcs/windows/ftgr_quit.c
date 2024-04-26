/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_on_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:22:11 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/16 23:22:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"

void ftgr_free(t_ftgr_ctx *ctx)
{
	if (ctx->main_window_class)
	{
		UnregisterClass(FTGR_WINDOW_CLASS, ctx->instance_handle);
		ctx->main_window_class = 0;
	}
	t_list *curr = ctx->windows;
	while (curr)
	{
		t_ftgr_win *win = curr->content;
		ftgr_free_window(win);
		curr = curr->next;
	}

	if (ctx->instance_handle)
	{
		FreeLibrary(ctx->instance_handle);
		ctx->instance_handle = NULL;
	}

	free(ctx);
}

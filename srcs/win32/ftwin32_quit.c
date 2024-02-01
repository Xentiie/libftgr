/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftwin32_on_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:22:11 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/16 23:22:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftwin32_int.h"

void ftwin32_set_quit_handler(t_ftwin32_ctx *ctx, void (*handler)())
{
	ctx->on_quit = handler;
}

void ftwin32_quit(t_ftwin32_ctx *ctx)
{
	ctx->run = FALSE;

	(ctx->on_quit)();

	ft_lstclear(&ctx->loop_hooks, NULL);

	if (ctx->main_window_class)
	{
		UnregisterClass(FTWIN32_WINDOW_CLASS, ctx->instance_handle);
		ctx->main_window_class = 0;
	}
	t_list *curr = ctx->windows;
	while (curr)
	{
		t_ftwin32_win *win = curr->content;
		ftwin32_free_window(win);
		curr = curr->next;
	}

	if (ctx->instance_handle)
	{
		FreeLibrary(ctx->instance_handle);
		ctx->instance_handle = NULL;
	}

	free(ctx);
}

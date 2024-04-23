/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:56:12 by reclaire          #+#    #+#             */
/*   Updated: 2024/04/23 00:08:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"

void ftgr_free(t_ftgr_ctx *ctx)
{
    t_list *win = ctx->windows;
    while (win)
    {
		t_list *nxt = win->next;
        ftgr_free_window(FTGR_WINDOW(win));
		free(win);
        win = nxt;
    }


    XFreeColormap(ctx->display, ctx->cmap);
    XDestroyWindow(ctx->display, ctx->root);
    XCloseDisplay(ctx->display);
    free(ctx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_ctx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:06:29 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 18:06:29 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_win_int.h"

#ifdef FT_OS_WIN

t_ftgr_ctx   *ftgr_create_ctx()
{
    t_ftgr_ctx   *ctx = malloc(sizeof(t_ftgr_ctx));
	if (!ctx)
		return NULL;


    ctx->instance_handle = GetModuleHandleW(NULL);
	if (!ctx->instance_handle)
	{
		_ftgr_error();
		free(ctx);
		return NULL;
	}

	ctx->main_window_class = 0;

	ctx->windows = NULL;

	clk_get(&ctx->global_time);
	clk_get(&ctx->delta_time_clk);

	for (U32 i = 0; i < sizeof(ctx->keys)/sizeof(ctx->keys[0]); i++)
		ctx->keys[i] = (t_key){0, 0, 0};

	ctx->left_mouse_pressed = FALSE;
	ctx->left_mouse_clicked = FALSE;
	ctx->middle_mouse_pressed = FALSE;
	ctx->middle_mouse_clicked = FALSE;
	ctx->right_mouse_pressed = FALSE;
	ctx->right_mouse_clicked = FALSE;

	ctx->widget_root = ftgr_new_widget();

	return ctx;
}

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

/*
    XFreeColormap(ctx->display, ctx->cmap);
    XDestroyWindow(ctx->display, ctx->root);
    XCloseDisplay(ctx->display);
*/
    free(ctx);
}

#endif
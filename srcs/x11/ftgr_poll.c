/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 23:27:29 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 18:06:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"

static bool find_event_win(void *w1, void *w2)
{
	t_ftgr_win *win1 = (t_ftgr_win *)w1;
	Window *win2 = (Window *)w2;

	return win1->window == *win2;
}

static void update_time(t_ftgr_ctx *ctx)
{
	t_time tmp;
	clk_get(&tmp);
	ctx->delta_time = clk_diff_float(&ctx->delta_time_clk, &tmp);
	ctx->delta_time_clk = tmp;
}

bool ftgr_wait(t_ftgr_ctx *ctx)
{
	while (!XPending(ctx->display))
		;
	return ftgr_poll(ctx);
}

bool ftgr_poll(t_ftgr_ctx *ctx)
{
	update_time(ctx);
	_ftx11_keys_cleanup(ctx);
	while (XPending(ctx->display))
	{
		XEvent ev;
		XNextEvent(ctx->display, &ev);

		t_list *win_lst = ft_lstfind(ctx->windows, find_event_win, &ev.xany.window);
		if (!win_lst)
			continue;

		if (ev.type == ClientMessage && ev.xclient.message_type == ctx->protocols_atom && (long unsigned int)ev.xclient.data.l[0] == ctx->del_win_atom)
			return FALSE;

		KeySym keysym;
		U32 key_uni;
		switch (ev.type)
		{
		case KeyPress:
			XLookupString(&ev.xkey, NULL, 0, &keysym, NULL);
			key_uni = _ftgr_keysym2uni(keysym);
			_ftx11_register_key_down(ctx, key_uni);
			//printf("Pressed key: %lc\n", key_uni);
			break;

		case KeyRelease:
			XLookupString(&ev.xkey, NULL, 0, &keysym, NULL);
			key_uni = _ftgr_keysym2uni(keysym);
			_ftx11_register_key_up(ctx, key_uni);
			//printf("Released key: %lc\n", key_uni);
			break;

		default:
			break;
		}
	}
	XSync(ctx->display, False);
	return TRUE;
}

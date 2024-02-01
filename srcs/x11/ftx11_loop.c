/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx11_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 23:27:29 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 18:06:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftx11_int.h"
#include <wchar.h>

static bool find_event_win(void *w1, void *w2)
{
	t_ftx11_win *win1 = (t_ftx11_win *)w1;
	Window *win2 = (Window *)w2;

	return win1->window == *win2;
}

void call_loop_hook(void *func)
{
	((void (*)())(func))();
}

void ftx11_loop(t_ftx11_ctx *ctx)
{
	// ftx11_int_set_win_event_mask(ctx);
	ctx->flush = 0;
	ctx->run = TRUE;
	while (ft_lstsize(ctx->windows) && ctx->run)
	{
		while (ctx->run && (!ctx->loop_hooks || XPending(ctx->display)))
		{
			XEvent ev;
			XNextEvent(ctx->display, &ev);

			t_list *win_lst = ft_lstfind(ctx->windows, find_event_win, &ev.xany.window);
			if (!win_lst)
				continue;

			// t_ftx11_win *win = FTX11_WINDOW(win_lst);
			if (ev.type == ClientMessage && ev.xclient.message_type == ctx->protocols_atom && (long unsigned int)ev.xclient.data.l[0] == ctx->del_win_atom)
			{
				// TODO: ON CLOSE
			}

			// TODO: events
			// if (win && ev.type < ftx11_MAX_EVENT && win->hooks[ev.type].hook)
			//	ftx11_int_param_event[ev.type](ctx, &ev, win);

			switch (ev.type)
			{
			case KeyPress:
				KeySym keysym;
				XLookupString(&ev.xkey, NULL, 0, &keysym, NULL);

				U32 key_uni = _ftx11_keysym2uni(keysym);
				printf("Pressed key: %lc\n", key_uni);

				break;

			case KeyRelease:
				break;

			default:
				break;
			}
		}
		XSync(ctx->display, False);

		ft_lstiter(ctx->loop_hooks, call_loop_hook);
	}
}

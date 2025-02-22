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

#include "libftgr_x11_int.h"
#ifdef FT_OS_LINUX

static bool find_event_win(void *w1, void *w2)
{
	t_ftgr_win_int *win1 = FTGR_WINDOW_INT((t_ftgr_win *)w1);
	Window *win2 = (Window *)w2;

	return win1->window == *win2;
}

static void update_time(t_ftgr_ctx *ctx)
{
	t_time tmp;
	ft_clk_get(&tmp);
	ctx->delta_time = ft_clk_diff_float(&ctx->delta_time_clk, &tmp);
	ctx->delta_time_clk = tmp;
}

static S32 get_key_mods(XKeyEvent xkey)
{
	const S32 ftgr_mods[][2] = {
		{ShiftMask, FTGR_KEYMOD_SHIFT},
		{ControlMask, FTGR_KEYMOD_CONTROL},
		{LockMask, FTGR_KEYMOD_CAPSLOCK},
		{Mod1Mask, FTGR_KEYMOD_ALT},
		{Mod2Mask, FTGR_KEYMOD_NUMLOCK},
		{Mod4Mask, FTGR_KEYMOD_SUPER},
	};

	S32 mods = 0;
	for (U64 i = 0; i < (sizeof(ftgr_mods) / sizeof(ftgr_mods[0])); i++)
	{
		if (xkey.state & ftgr_mods[i][0])
			mods |= ftgr_mods[i][1];
	}
	return mods;
}

bool ftgr_poll(t_ftgr_ctx *ctx)
{
	XEvent ev;
	t_list *win_lst;
	KeySym keysym;
	U32 key_uni;
	/* key modifiers */
	S32 mods;

	update_time(ctx);
	//TODO: also cleanup mouse, bad
	//TODO: rename
	_ftx11_keys_cleanup(ctx);

	while (XPending(ctx->display))
	{
		XNextEvent(ctx->display, &ev);

		if ((win_lst = ft_lstfind(ctx->windows, find_event_win, &ev.xany.window)) == NULL)
			continue;

		if (ev.type == ClientMessage && ev.xclient.message_type == ctx->protocols_atom && (long unsigned int)ev.xclient.data.l[0] == ctx->del_win_atom)
			return FALSE;

		(void)mods;
		switch (ev.type)
		{
		case KeyPress:
		case KeyRelease:
			mods = get_key_mods(ev.xkey);
			XLookupString(&ev.xkey, NULL, 0, &keysym, NULL);
			key_uni = _ftgr_keysym2uni(keysym);

			if (ev.type == KeyPress)
			{
				_ftx11_register_key_down(ctx, key_uni);
				// printf("Pressed key: %lc\n", key_uni);
			}
			else
			{
				_ftx11_register_key_up(ctx, key_uni);
				// printf("Released key: %lc\n", key_uni);
			}
			break;

		case ButtonPress:;
			ctx->mouse[(ev.xbutton.button - 1) % 3] = _FTGR_MOUSE_DOWN;
			break;
		case ButtonRelease:
			ctx->mouse[(ev.xbutton.button - 1) % 3] = FALSE;
			break;

		default:
			break;
		}
	}
	XSync(ctx->display, False);
	return TRUE;
}

bool ftgr_wait(t_ftgr_ctx *ctx)
{
	XEvent ev;

	XNextEvent(ctx->display, &ev);
	XPutBackEvent(ctx->display, &ev);
	return ftgr_poll(ctx);
}

#endif
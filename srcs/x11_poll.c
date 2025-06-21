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

#include "libftGFX_x11.h"

#include "libft/bits/static_array_len.h"

#if FT_OS_LINUX

MAYBE_UNUSED
static string get_event_name(S32 event)
{
	string event_names[] = {
		"",
		"",
		"KeyPress",
		"KeyRelease",
		"ButtonPress",
		"ButtonRelease",
		"MotionNotify",
		"EnterNotify",
		"LeaveNotify",
		"FocusIn",
		"FocusOut",
		"KeymapNotify",
		"Expose",
		"GraphicsExpose",
		"NoExpose",
		"VisibilityNotify",
		"CreateNotify",
		"DestroyNotify",
		"UnmapNotify",
		"MapNotify",
		"MapRequest",
		"ReparentNotify",
		"ConfigureNotify",
		"ConfigureRequest",
		"GravityNotify",
		"ResizeRequest",
		"CirculateNotify",
		"CirculateRequest",
		"PropertyNotify",
		"SelectionClear",
		"SelectionRequest",
		"SelectionNotify",
		"ColormapNotify",
		"ClientMessage",
		"MappingNotify",
		"GenericEvent",
	};
	if (event >= (S32)statarray_len(event_names) || event < 0)
		return NULL;
	return event_names[event];
}

static S32 get_key_mods(XKeyEvent xkey)
{
	const S32 modifiers[][2] = {
		{ShiftMask, FTGFX_KEYMOD_SHIFT},
		{ControlMask, FTGFX_KEYMOD_CONTROL},
		{LockMask, FTGFX_KEYMOD_CAPSLOCK},
		{Mod1Mask, FTGFX_KEYMOD_ALT},
		{Mod2Mask, FTGFX_KEYMOD_NUMLOCK},
		{Mod4Mask, FTGFX_KEYMOD_SUPER},
	};

	S32 mods;

	mods = 0;
	for (U64 i = 0; i < (sizeof(modifiers) / sizeof(modifiers[0])); i++)
	{
		if (xkey.state & modifiers[i][0])
			mods |= modifiers[i][1];
	}
	return mods;
}

static void fill_key_event(XEvent *x_event, struct s_ftGFX_event *event)
{
	KeySym keysym;

	event->key.modifiers = get_key_mods(x_event->xkey);
	XLookupString(&x_event->xkey, NULL, 0, &keysym, NULL);
	event->key.unicode = ftgfxx11_keysym_to_unicode(keysym);
}

static void fill_mouse_button_event(XEvent *x_event, struct s_ftGFX_event *event)
{
	event->mouse.button = ftgfxx11_x11_to_ftgfx_mouse_button(x_event->xbutton.button);
	event->mouse.pos = ivec2(x_event->xbutton.x, x_event->xbutton.y);
}

static void fill_mouse_move_event(XEvent *x_event, struct s_ftGFX_event *event)
{
	event->mouse.button = (enum e_ftGFX_mouse_button) - 1;
	event->mouse.pos = ivec2(x_event->xmotion.x, x_event->xmotion.y);
}

static void fill_mouse_crossing_event(XEvent *x_event, struct s_ftGFX_event *event)
{
	event->mouse.button = (enum e_ftGFX_mouse_button) - 1;
	event->mouse.pos = ivec2(x_event->xcrossing.x, x_event->xcrossing.y);
}

static void fill_expose_event(XEvent *x_event, struct s_ftGFX_event *event)
{
	event->damage.rect = ivec4(
		x_event->xexpose.x,
		x_event->xexpose.y,
		x_event->xexpose.x + x_event->xexpose.width,
		x_event->xexpose.y + x_event->xexpose.height);
}

static void fill_focus_event(XEvent *x_event, struct s_ftGFX_event *event)
{
	(void)x_event;
	(void)event;
}

void ftGFX_new_frame(struct s_ftGFX_ctx *ctx)
{
	t_time new_time;
	ftgfxx11_keys_reset(ctx);

	{ /* Update time it took to process last frame. */
		ft_clk_get(&new_time);
		ctx->delta_time = ft_clk_diff_float(&ctx->delta_time_clk, &new_time);
		ctx->delta_time_clk = new_time;
	}
}

bool ftGFX_poll(struct s_ftGFX_ctx *ctx, struct s_ftGFX_event *event)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window *win;
	struct s_ftGFX_window_private *win_private;

	struct s_ftGFX_event dummy_event;

	XEvent ev;

	private = (struct s_ftGFX_ctx_private *)ctx->private;
	if (event == NULL)
		event = &dummy_event;

repoll:
	if (!XPending(private->display))
		return FALSE;

	XNextEvent(private->display, &ev);

	win = ctx->windows;
	while (win)
	{
		win_private = (struct s_ftGFX_window_private *)win->private;
		if (win_private->window == ev.xany.window)
			break;
		win = win->next;
	}
	if (win == NULL)
		goto repoll;

	if (ev.type == ClientMessage && ev.xclient.message_type == private->protocols_atom && (long unsigned int)ev.xclient.data.l[0] == private->del_win_atom)
	{
		ctx->should_close = TRUE;
		goto repoll;
	}

	switch (ev.type)
	{
	case KeyPress:
		event->type = FTGFX_KEY_PRESS_EVENT;
		fill_key_event(&ev, event);
		if (event->key.unicode < statarray_len(ctx->keys))
			ctx->keys[event->key.unicode] = FTGFX_KEY_PRESSED;
		break;

	case KeyRelease:
		event->type = FTGFX_KEY_RELEASE_EVENT;
		fill_key_event(&ev, event);
		if (event->key.unicode < statarray_len(ctx->keys))
			ctx->keys[event->key.unicode] = FTGFX_KEY_RELEASED;
		break;

	case ButtonPress:
		event->type = FTGFX_MOUSE_PRESS_EVENT;
		fill_mouse_button_event(&ev, event);
		if (event->mouse.button < statarray_len(ctx->mouse))
			ctx->mouse[event->mouse.button] = FTGFX_MOUSE_PRESSED;
		break;

	case ButtonRelease:
		event->type = FTGFX_MOUSE_RELEASE_EVENT;
		fill_mouse_button_event(&ev, event);
		if (event->mouse.button < statarray_len(ctx->mouse))
			ctx->mouse[event->mouse.button] = FTGFX_MOUSE_RELEASED;
		break;

	case MotionNotify:
		event->type = FTGFX_MOUSE_MOVE_EVENT;
		fill_mouse_move_event(&ev, event);
		break;

	case EnterNotify:
		event->type = FTGFX_MOUSE_ENTER_EVENT;
		fill_mouse_crossing_event(&ev, event);
		break;

	case LeaveNotify:
		event->type = FTGFX_MOUSE_LEAVE_EVENT;
		fill_mouse_crossing_event(&ev, event);
		break;

	case Expose:
		event->type = FTGFX_WINDOW_DAMAGE_EVENT;
		fill_expose_event(&ev, event);
		break;

	case FocusIn:
		event->type = FTGFX_FOCUS_IN_EVENT;
		fill_focus_event(&ev, event);
		break;

	case FocusOut:
		event->type = FTGFX_FOCUS_OUT_EVENT;
		fill_focus_event(&ev, event);
		break;

		// TODO: SelectionRequest (clipboard)

	default:
		// ft_printf("%s (%d)\n", get_event_name(ev.type), ev.type);
		// if (ev.type == PropertyNotify)
		//{
		//	ft_printf("	%s\n", XGetAtomName(private->display, ev.xproperty.atom));
		// }
		goto repoll;
	}
	XSync(private->display, FALSE);

	return TRUE;
}

bool ftGFX_wait(struct s_ftGFX_ctx *ctx, struct s_ftGFX_event *event)
{
	struct s_ftGFX_ctx_private *private;
	XEvent ev;

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	XNextEvent(private->display, &ev);
	XPutBackEvent(private->display, &ev);
	return ftGFX_poll(ctx, event);
}

void ftGFX_poll_all(struct s_ftGFX_ctx *ctx)
{
	while (ftGFX_poll(ctx, NULL))
		;
}

#endif
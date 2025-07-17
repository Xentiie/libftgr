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

void ftGFX_new_frame(struct s_ftGFX_ctx *ctx)
{
	t_time new_time;
	struct s_ftGFX_window *window;

	window = ctx->windows;
	while (window)
	{
		ftgfxx11_window_reset(window);
		window = window->next;
	}

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

	// if (event && private->event_queue_len > 0)
	//{
	//	private->event_queue_len
	// }

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
		win->should_close = TRUE;
		goto repoll;
	}

	event->window = win;

	switch (ev.type)
	{
	case KeyPress:
	case KeyRelease:
		KeySym keysym;
		enum e_ftGFX_key key;

		key = ftgfxx11_x11_to_ftgfx_key(ctx, ev.xkey.keycode);

		/* Don't use XLookupString to convert the key event, as we can do it better */
		XLookupString(&ev.xkey, NULL, 0, &keysym, NULL);

		event->key.unicode = ftgfxx11_keysym_to_unicode(keysym);
		event->key.modifiers = ftgfxx11_x11_to_ftgfx_key_modifiers(ev.xkey.state);
		event->key.key = key;

		if (ev.type == KeyPress)
			event->type = FTGFX_KEY_PRESS_EVENT;
		else
			event->type = FTGFX_KEY_RELEASE_EVENT;
		break;

	case ButtonPress:
	case ButtonRelease:
		event->mouse.button = ftgfxx11_x11_to_ftgfx_mouse_button(ev.xbutton.button);
		event->mouse.modifiers = ftgfxx11_x11_to_ftgfx_key_modifiers(ev.xbutton.state);
		event->mouse.pos = ivec2(ev.xbutton.x, ev.xbutton.y);
		if (ev.type == ButtonPress)
			event->type = FTGFX_MOUSE_PRESS_EVENT;
		else
			event->type = FTGFX_MOUSE_RELEASE_EVENT;
		break;

	case MotionNotify:
		event->type = FTGFX_MOUSE_MOVE_EVENT;
		event->mouse.button = (enum e_ftGFX_mouse_button)(-1);
		event->mouse.pos = ivec2(ev.xmotion.x, ev.xmotion.y);
		break;

	case EnterNotify:
	case LeaveNotify:
		event->mouse.button = (enum e_ftGFX_mouse_button) - 1;
		event->mouse.pos = ivec2(ev.xcrossing.x, ev.xcrossing.y);
		if (ev.type == EnterNotify)
			event->type = FTGFX_MOUSE_ENTER_EVENT;
		else
			event->type = FTGFX_MOUSE_LEAVE_EVENT;
		break;

	case Expose:
		event->type = FTGFX_WINDOW_DAMAGE_EVENT;
		event->damage.rect = ivec4(
			ev.xexpose.x,
			ev.xexpose.y,
			ev.xexpose.x + ev.xexpose.width,
			ev.xexpose.y + ev.xexpose.height);
		break;

	case FocusIn:
		if (ev.type == FocusIn)
			event->type = FTGFX_FOCUS_IN_EVENT;
		else
			event->type = FTGFX_FOCUS_OUT_EVENT;
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

re_nextevent:
	XNextEvent(private->display, &ev);
	if (ev.type == NoExpose)
		goto re_nextevent;
	XPutBackEvent(private->display, &ev);
	return ftGFX_poll(ctx, event);
}

void ftGFX_poll_all(struct s_ftGFX_ctx *ctx)
{
	struct s_ftGFX_event event;

	while (ftGFX_poll(ctx, &event))
		ftGFX_process_event(&event);
}

void ftGFX_process_event(struct s_ftGFX_event *event)
{
	struct s_ftGFX_window *window;
	struct s_ftGFX_window_private *window_private;

	window = event->window;
	window_private = (struct s_ftGFX_window_private *)window->private;

	switch (event->type)
	{
	case FTGFX_MOUSE_PRESS_EVENT:
		if (event->mouse.button < statarray_len(window->mouse))
			window->mouse[event->mouse.button] = FTGFX_MOUSE_STATE_PRESSED;
		break;

	case FTGFX_MOUSE_RELEASE_EVENT:
		if (event->mouse.button < statarray_len(window->mouse))
			window->mouse[event->mouse.button] = FTGFX_MOUSE_STATE_RELEASED;
		break;

	case FTGFX_MOUSE_MOVE_EVENT:
		window->mouse_delta = ivec2_add(window->mouse_delta, ivec2_sub(event->mouse.pos, window_private->last_mouse_pos));
		window_private->last_mouse_pos = event->mouse.pos;
		break;

	case FTGFX_MOUSE_ENTER_EVENT:
		break;

	case FTGFX_MOUSE_LEAVE_EVENT:
		break;

	case FTGFX_KEY_PRESS_EVENT:
		if (event->key.key > FTGFX_KEY_UNKNOWN && (U64)event->key.key < statarray_len(window->keys))
			window->keys[event->key.key] = FTGFX_KEY_STATE_PRESSED;
		break;

	case FTGFX_KEY_RELEASE_EVENT:
		if (event->key.key > FTGFX_KEY_UNKNOWN && (U64)event->key.key < statarray_len(window->keys))
			window->keys[event->key.key] = FTGFX_KEY_STATE_RELEASED;
		break;

	case FTGFX_WINDOW_DAMAGE_EVENT:
		window->damage = ft_rect_max(window->damage, event->damage.rect);
		break;

	case FTGFX_FOCUS_IN_EVENT:
		window->ctx->active_window = window;
		break;

	case FTGFX_FOCUS_OUT_EVENT:
		if (window->ctx->active_window == window)
			window->ctx->active_window = NULL;
		break;

	default:
		break;
	}
}

#endif
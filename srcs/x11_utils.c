/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:38:56 by reclaire          #+#    #+#             */
/*   Updated: 2025/07/08 03:16:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftGFX_x11.h"

#if FT_OS_LINUX

#include "libft/bits/ft_return.h"

enum e_ftGFX_key ftgfxx11_x11_to_ftgfx_key(struct s_ftGFX_ctx *ctx, U32 keycode)
{
	struct s_ftGFX_ctx_private *private;
	KeySym key, key_lc, key_uc;

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	ft_errno = 0; /* Set ft_errno to 0 first, instead of writing FT_RET_OK over and over. */

	/* Try secondary keysym, for numeric keypad keys
	 * NOTE: This way we always force "NumLock = ON", which at least
	 * enables GLFW users to detect numeric keypad keys. */
	key = XKeycodeToKeysym(private->display, keycode, 1);
	switch (key)
	{
	/* Numeric keypad. */
	case XK_KP_0:
		return FTGFX_KEY_KP_0;
	case XK_KP_1:
		return FTGFX_KEY_KP_1;
	case XK_KP_2:
		return FTGFX_KEY_KP_2;
	case XK_KP_3:
		return FTGFX_KEY_KP_3;
	case XK_KP_4:
		return FTGFX_KEY_KP_4;
	case XK_KP_5:
		return FTGFX_KEY_KP_5;
	case XK_KP_6:
		return FTGFX_KEY_KP_6;
	case XK_KP_7:
		return FTGFX_KEY_KP_7;
	case XK_KP_8:
		return FTGFX_KEY_KP_8;
	case XK_KP_9:
		return FTGFX_KEY_KP_9;
	case XK_KP_Separator:
	case XK_KP_Decimal:
		return FTGFX_KEY_KP_DECIMAL;
	case XK_KP_Equal:
		return FTGFX_KEY_KP_EQUAL;
	case XK_KP_Enter:
		return FTGFX_KEY_KP_ENTER;
	default:
		break;
	}

	/* Now try pimary keysym. */
	key = XKeycodeToKeysym(private->display, keycode, 0);
	switch (key)
	{
	/* Special keys (non character keys). */
	case XK_Escape:
		return FTGFX_KEY_ESC;
	case XK_Tab:
		return FTGFX_KEY_TAB;
	case XK_Shift_L:
		return FTGFX_KEY_LSHIFT;
	case XK_Shift_R:
		return FTGFX_KEY_RSHIFT;
	case XK_Control_L:
		return FTGFX_KEY_LCTRL;
	case XK_Control_R:
		return FTGFX_KEY_RCTRL;
	case XK_Meta_L:
	case XK_Alt_L:
		return FTGFX_KEY_LALT;
	case XK_Mode_switch: /* Mapped to Alt_R on many keyboards. */
	case XK_Meta_R:
	case XK_ISO_Level3_Shift: /* AltGr on at least some machines. */
	case XK_Alt_R:
		return FTGFX_KEY_RALT;
	case XK_Super_L:
		return FTGFX_KEY_LSUPER;
	case XK_Super_R:
		return FTGFX_KEY_RSUPER;
	case XK_Menu:
		return FTGFX_KEY_MENU;
	case XK_Num_Lock:
		return FTGFX_KEY_KP_NUM_LOCK;
	case XK_Caps_Lock:
		return FTGFX_KEY_CAPS_LOCK;
	case XK_Scroll_Lock:
		return FTGFX_KEY_SCROLL_LOCK;
	case XK_Pause:
		return FTGFX_KEY_PAUSE;
	case XK_KP_Delete:
	case XK_Delete:
		return FTGFX_KEY_DEL;
	case XK_BackSpace:
		return FTGFX_KEY_BACKSPACE;
	case XK_Return:
		return FTGFX_KEY_ENTER;
	case XK_KP_Home:
	case XK_Home:
		return FTGFX_KEY_HOME;
	case XK_KP_End:
	case XK_End:
		return FTGFX_KEY_END;
	case XK_KP_Page_Up:
	case XK_Page_Up:
		return FTGFX_KEY_PAGEUP;
	case XK_KP_Page_Down:
	case XK_Page_Down:
		return FTGFX_KEY_PAGEDOWN;
	case XK_KP_Insert:
	case XK_Insert:
		return FTGFX_KEY_INSERT;
	case XK_KP_Left:
	case XK_Left:
		return FTGFX_KEY_LEFT;
	case XK_KP_Right:
	case XK_Right:
		return FTGFX_KEY_RIGHT;
	case XK_KP_Down:
	case XK_Down:
		return FTGFX_KEY_DOWN;
	case XK_KP_Up:
	case XK_Up:
		return FTGFX_KEY_UP;
	case XK_F1:
		return FTGFX_KEY_F1;
	case XK_F2:
		return FTGFX_KEY_F2;
	case XK_F3:
		return FTGFX_KEY_F3;
	case XK_F4:
		return FTGFX_KEY_F4;
	case XK_F5:
		return FTGFX_KEY_F5;
	case XK_F6:
		return FTGFX_KEY_F6;
	case XK_F7:
		return FTGFX_KEY_F7;
	case XK_F8:
		return FTGFX_KEY_F8;
	case XK_F9:
		return FTGFX_KEY_F9;
	case XK_F10:
		return FTGFX_KEY_F10;
	case XK_F11:
		return FTGFX_KEY_F11;
	case XK_F12:
		return FTGFX_KEY_F12;
	case XK_F13:
		return FTGFX_KEY_F13;
	case XK_F14:
		return FTGFX_KEY_F14;
	case XK_F15:
		return FTGFX_KEY_F15;
	case XK_F16:
		return FTGFX_KEY_F16;
	case XK_F17:
		return FTGFX_KEY_F17;
	case XK_F18:
		return FTGFX_KEY_F18;
	case XK_F19:
		return FTGFX_KEY_F19;
	case XK_F20:
		return FTGFX_KEY_F20;
	case XK_F21:
		return FTGFX_KEY_F21;
	case XK_F22:
		return FTGFX_KEY_F22;
	case XK_F23:
		return FTGFX_KEY_F23;
	case XK_F24:
		return FTGFX_KEY_F24;
	case XK_F25:
		return FTGFX_KEY_F25;

	/* Numeric keypad (should have been detected in secondary keysym !). */
	case XK_KP_Divide:
		return FTGFX_KEY_KP_DIVIDE;
	case XK_KP_Multiply:
		return FTGFX_KEY_KP_MULTIPLY;
	case XK_KP_Subtract:
		return FTGFX_KEY_KP_SUBTRACT;
	case XK_KP_Add:
		return FTGFX_KEY_KP_ADD;
	case XK_KP_Equal:
		return FTGFX_KEY_KP_EQUAL;
	case XK_KP_Enter:
		return FTGFX_KEY_KP_ENTER;

	/* The rest (should be printable keys). */
	default:
		/* Make uppercase. */
		XConvertCase(key, &key_lc, &key_uc);
		key = key_uc;

		/* Valid ISO 8859-1 character ? */
		if ((key >= 32 && key <= 126) || (key >= 160 && key <= 255))
			return (enum e_ftGFX_key)key;

		FT_RET_ERR(FTGFX_KEY_UNKNOWN, FT_ERANGE);
	}
}

U8 ftgfxx11_x11_to_ftgfx_mouse_button(U32 x11_mouse_button)
{
	const U8 x11_to_ftgfx[] = {
		[0] = (U8)-1, /* Invalid */
		[1] = FTGFX_MOUSE_LEFT,
		[2] = FTGFX_MOUSE_MIDDLE,
		[3] = FTGFX_MOUSE_RIGHT,
		[4] = FTGFX_MOUSE_SCROLLWHEEL_UP,
		[5] = FTGFX_MOUSE_SCROLLWHEEL_DOWN,
		[6] = FTGFX_MOUSE_SCROLLWHEEL_PUSH_LEFT,
		[7] = FTGFX_MOUSE_SCROLLWHEEL_PUSH_RIGHT,
		[8] = FTGFX_MOUSE_SIDE_1,
		[9] = FTGFX_MOUSE_SIDE_2,	
	};

	if (x11_mouse_button > statarray_len(x11_to_ftgfx))
		FT_RET_ERR((U8)-1, FT_ERANGE);
	return x11_to_ftgfx[x11_mouse_button];
}

U32 ftgfxx11_x11_to_ftgfx_key_modifiers(U32 x11_mods)
{
	const U32 modifiers[][2] = {
		{ShiftMask, FTGFX_KEYMOD_SHIFT},
		{ControlMask, FTGFX_KEYMOD_CONTROL},
		{LockMask, FTGFX_KEYMOD_CAPSLOCK},
		{Mod1Mask, FTGFX_KEYMOD_ALT},
		{Mod2Mask, FTGFX_KEYMOD_NUMLOCK},
		{Mod4Mask, FTGFX_KEYMOD_SUPER},
	};

	U32 mods;

	mods = 0;
	for (U64 i = 0; i < (sizeof(modifiers) / sizeof(modifiers[0])); i++)
	{
		if (x11_mods & modifiers[i][0])
			mods |= modifiers[i][1];
	}
	return mods;
}

t_iv2 ftGFX_get_screen_size(struct s_ftGFX_ctx *ctx)
{
	struct s_ftGFX_ctx_private *private;
	XWindowAttributes	attr;

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	XGetWindowAttributes(private->display, private->root, &attr);
	return ivec2(attr.width, attr.height);
}

#endif
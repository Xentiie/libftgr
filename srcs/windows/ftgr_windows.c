/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_new_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:06:24 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 18:06:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int.h"

#include <stdio.h>

LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	t_ftgr_win *win = GetPropW(hwnd, FTGR_PROP_NAME);
	if (!win)
		return DefWindowProc(hwnd, msg, wParam, lParam);
	t_ftgr_ctx *ctx = win->ctx;

	switch (msg)
	{
	case WM_ERASEBKGND:
		return 1;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (!ctx->key_autorepeat && (lParam >> 30) & 1)
			return 0;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		if (0)
		{
		}

		// FALSE: release, TRUE: pressed
		bool action = (HIWORD(lParam) & KF_UP) ? FALSE : TRUE;

		char state[256] = {0}, buffer[2] = {0};
		WCHAR chars[16];

		U32 scan_code = (lParam >> 16) & 0xFF;
		U32 k = MapVirtualKey(scan_code, MAPVK_VSC_TO_VK);
		ToUnicode(k, scan_code, state, chars, sizeof(chars) / sizeof(WCHAR), 0);
		WideCharToMultiByte(CP_UTF8, 0, chars, 1,
							buffer,
							sizeof(buffer),
							NULL, NULL);

		if (action)
			_ftwin32_register_key_down(ctx, buffer[0]);
		else
			_ftwin32_register_key_up(ctx, buffer[0]);

		return 0;

	case WM_SETCURSOR:
		if (win->cursor_mode & FTGR_CURSOR_HIDDEN && LOWORD(lParam) == HTCLIENT)
			SetCursor(NULL);
		return TRUE;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		ctx->left_mouse_clicked |= !!(wParam & 0x0001);
		ctx->middle_mouse_clicked |= !!(wParam & 0x0010);
		ctx->right_mouse_clicked |= !!(wParam & 0x0002);
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		ctx->left_mouse_pressed = !!(wParam & 0x0001);
		ctx->middle_mouse_pressed = !!(wParam & 0x0010);
		ctx->right_mouse_pressed = !!(wParam & 0x0002);
		return FALSE;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

}

t_ftgr_win *ftgr_new_window(t_ftgr_ctx *ctx, t_iv2 size, const_string title)
{

	t_ftgr_win *win = malloc(sizeof(t_ftgr_win));
	if (win == NULL)
		return NULL;
	ft_memset(win, 0, sizeof(t_ftgr_win));

	win->ctx = ctx;
	if (!ctx->main_window_class)
	{
		WNDCLASSEX wc = {0};
		wc.lpszClassName = FTGR_WINDOW_CLASS;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpfnWndProc = windowProc;
		wc.hInstance = ctx->instance_handle;
		wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
		wc.lpszMenuName = NULL;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;

		ctx->main_window_class = RegisterClassEx(&wc);
		if (ctx->main_window_class == 0)
		{
			_ftgr_error();
			free(win);
			return NULL;
		}
	}

	win->window_handle = CreateWindowEx(
		0,					  // Extended window style
		FTGR_WINDOW_CLASS,	  // Class name
		title,				  // Window title
		WS_OVERLAPPEDWINDOW,  // Window style
		CW_USEDEFAULT,		  // X position
		CW_USEDEFAULT,		  // Y position
		size.x,				  // Width
		size.y,				  // Height
		NULL,				  // Parent window
		NULL,				  // Menu
		ctx->instance_handle, // Instance handle
		NULL				  // Additional application data
	);

	if (win->window_handle == NULL)
	{
		_ftgr_error();
		free(win);
		return NULL;
	}

	t_list *lst;
	ShowWindow(win->window_handle, SW_SHOWNORMAL);
	if (UpdateWindow(win->window_handle) == FALSE ||
		SetPropW(win->window_handle, FTGR_PROP_NAME, win) == FALSE ||
		((lst = ft_lstnew(win)) == NULL || ft_errno != FT_OK) ||
		((win->name = ft_strdup(title)) == NULL || ft_errno != FT_OK) ||
		(win->dc = GetDC(win->window_handle)) == NULL)
	{
		_ftgr_error();
		ftgr_free_window(win);
		return NULL;
	}

	ft_lstadd_front(&ctx->windows, lst);

	win->cursor_mode = FTGR_CURSOR_NORMAL;
	win->name = ft_strdup(title);

	return win;
}

static bool _find_win(void *w1, void *w2)
{
	return w1 == w2;
}

void ftgr_free_window(t_ftgr_win *win)
{
	if (win->window_handle)
	{
		if (win->dc)
			CHECKRET(ReleaseDC(win->window_handle, win->dc) == FALSE);
		int ret = DestroyWindow(win->window_handle);
		// Ne pas changer, documentation dis que on doit check explicitement pour TRUE/FALSE
		if (ret == FALSE)
			_ftgr_error();
		win->window_handle = NULL;
	}

	t_list *lst = ft_lstfind(win->ctx->windows, _find_win, win);
	if (lst)
		ft_lstremove(&win->ctx->windows, lst, NULL);
	free(win);
}

void ftgr_bring_top(t_ftgr_win *win)
{
	// ShowWindow(win->window_handle, SW_SHOWNA);
	// BringWindowToTop(win->window_handle);
	// SetForegroundWindow(win->window_handle);
	// SetFocus(win->window_handle);
}

void ftgr_set_win_name(t_ftgr_win *win, string name)
{
	LIMIT_FREQ(1);
	free(win->name);
	win->name = ft_strdup(name);
	if (SetWindowTextA(win->window_handle, win->name) == FALSE)
		_ftgr_error();
}

void ftgr_set_win_name_infos(t_ftgr_win *win, string infos)
{
	LIMIT_FREQ(1);
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "%s - %s", win->name, infos);
	if (SetWindowTextA(win->window_handle, buffer) == FALSE)
		_ftgr_error();
}

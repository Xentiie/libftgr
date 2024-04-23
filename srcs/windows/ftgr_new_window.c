/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftwin32_new_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:06:24 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/12 18:06:24 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftwin32_int.h"

#include <stdio.h>

LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	t_ftwin32_win *win = GetPropW(hwnd, FTWIN32_PROP_NAME);

	switch (msg)
	{

	case WM_CLOSE:
		ftwin32_quit(win->ctx);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;

	case WM_SETCURSOR:
		printf("%d\n", win->cursor_mode & FTGR_CURSOR_HIDDEN);
		if (win->cursor_mode & FTGR_CURSOR_HIDDEN && LOWORD(lParam) == HTCLIENT)
			SetCursor(NULL);
		return TRUE;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

t_ftwin32_win *ftwin32_new_window(t_ftwin32_ctx *ctx, t_iv2 size, const_string title)
{

	t_ftwin32_win *win = malloc(sizeof(t_ftwin32_win));
	if (win == NULL)
		return NULL;

	win->ctx = ctx;
	if (!ctx->main_window_class)
	{
		WNDCLASSEXW wc = {0};
		wc.lpfnWndProc = windowProc;
		wc.hInstance = ctx->instance_handle;
		wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
		wc.lpszClassName = FTWIN32_WINDOW_CLASS;

		ctx->main_window_class = RegisterClassExW(&wc);
		if (ctx->main_window_class == 0)
		{
			_ftwin32_error(ctx);
			free(win);
			return NULL;
		}
	}

	win->window_handle = CreateWindowEx(
		0,					  // Extended window style
		FTWIN32_WINDOW_CLASS, // Class name
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
		_ftwin32_error(ctx);
		free(win);
		return NULL;
	}

	ShowWindow(win->window_handle, SW_SHOWNORMAL);
	UpdateWindow(win->window_handle);

	win->cursor_mode = FTGR_CURSOR_NORMAL;

	t_list *lst = ft_lstnew(win);
	if (ft_errno != FT_OK)
	{
		_ftwin32_error(ctx);
		ftwin32_free_window(win);
		return NULL;
	}
	ft_lstadd_front(&ctx->windows, lst);

	if (SetPropW(win->window_handle, FTWIN32_PROP_NAME, win) == FALSE)
	{
		_ftwin32_error(ctx);
		ftwin32_free_window(win);
		return NULL;
	}

	return win;
}

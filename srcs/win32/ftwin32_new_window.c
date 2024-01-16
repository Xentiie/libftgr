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
	t_ftwin32_win	*win = GetPropW(hwnd, FTWIN32_PROP_NAME);

	printf("WINDOW: %p\n", win);

	switch (msg)
	{
	case WM_CLOSE:
		// Handle the close event
		if (MessageBox(win->window_handle, "Do you really want to quit?", "Quit", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(win->window_handle);
		}
		return 0;

	case WM_DESTROY:
		// Handle the destroy event
		PostQuitMessage(0);
		return 0;
	}

	// Pass unhandled messages to the default window procedure
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

t_ftwin32_win *ftwin32_new_window(t_ftwin32_ctx *ctx, t_iv2 size, const_string title)
{

	t_ftwin32_win	*win = malloc(sizeof(t_ftwin32_win));

	win->ctx = ctx;
	if (!ctx->main_window_class)
	{
		WNDCLASS wc = {0};
		wc.lpfnWndProc = windowProc;
		wc.hInstance = ctx->instance_handle;
		wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
		wc.lpszClassName = FTWIN32_WINDOW_CLASS;

		ctx->main_window_class = RegisterClass(&wc);
	}

	win->window_handle = CreateWindowEx(
        0,                          // Extended window style
        FTWIN32_WINDOW_CLASS,       // Class name
        title,                		// Window title
        WS_OVERLAPPEDWINDOW,        // Window style
        CW_USEDEFAULT,              // X position
        CW_USEDEFAULT,              // Y position
        size.x,                     // Width
        size.y,                     // Height
        NULL,                       // Parent window
        NULL,                       // Menu
        ctx->instance_handle,       // Instance handle
        NULL                        // Additional application data
    );

    if (!win->window_handle) {
        MessageBox(NULL, "Window creation failed!", "Error", MB_ICONERROR);
        return NULL;
    }

	SetPropW(win->window_handle, FTWIN32_PROP_NAME, win);

    ShowWindow(win->window_handle, SW_SHOWNORMAL);
    UpdateWindow(win->window_handle);

	t_list	*lst = ft_lstnew(win);
	ft_lstadd_front(&ctx->windows, lst);

	return win;
}

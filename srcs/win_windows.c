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

#include "libftgr_win_int.h"

#ifdef FT_OS_WIN
#include <windowsx.h>
#include <stdio.h>

LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
static inline ATOM _init_main_window_class(HINSTANCE hInstance);
static inline HWND _create_window(const_string title, t_iv2 size, HINSTANCE hInstance);
static inline bool _init_buffer(t_ftgr_img *buffer, t_iv2 size);

#define RESIZE_TIMER_DELAY 300 // ms
#define RESIZE_TIMER 1		   // For WM_TIMER
LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	t_ftgr_win *win = FTGR_GET_HWIN_t_ftgr_window(hwnd);
	if (!win)
		return DefWindowProc(hwnd, msg, wParam, lParam);
	t_ftgr_ctx *ctx = win->ctx;
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	switch (msg)
	{
	case WM_ERASEBKGND:
		return 1;

	case WM_DESTROY:
		// TODO: ici ca fait quitter toute l'app.
		// on veut seulement fermer une fenetre
		PostQuitMessage(0);
		return FALSE;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (!ctx->key_autorepeat && (lParam >> 30) & 1)
			return 0;
		/* fallthrough */
	case WM_KEYUP:
	case WM_SYSKEYUP:;
		// FALSE: release, TRUE: pressed
		bool action = (HIWORD(lParam) & KF_UP) ? FALSE : TRUE;

		char state[256] = {0}, buffer[2] = {0};
		WCHAR chars[16];

		U32 scan_code = (lParam >> 16) & 0xFF;
		U32 k = MapVirtualKey(scan_code, MAPVK_VSC_TO_VK);
		ToUnicode(k, scan_code, (char *)state, chars, sizeof(chars) / sizeof(WCHAR), 0);
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
		if (LOWORD(lParam) == HTCLIENT)
			SetCursor(ctx->defaultCursor);
		return DefWindowProc(hwnd, msg, wParam, lParam);

		// case WM_SETCURSOR:
		//	if (win->cursor_mode & FTGR_CURSOR_HIDDEN && LOWORD(lParam) == HTCLIENT)
		//		SetCursor(NULL);
		//	return TRUE;

	case WM_LBUTTONDOWN:
		ctx->left_mouse_clicked = TRUE;
		ctx->left_mouse_pressed = TRUE;
		return FALSE;
	case WM_MBUTTONDOWN:
		ctx->middle_mouse_clicked = TRUE;
		ctx->left_mouse_pressed = TRUE;
		return FALSE;
	case WM_RBUTTONDOWN:
		ctx->right_mouse_clicked = TRUE;
		ctx->left_mouse_pressed = TRUE;
		return FALSE;

	case WM_LBUTTONUP:
		ctx->right_mouse_clicked = FALSE;
		ctx->left_mouse_pressed = FALSE;
		ctx->left_mouse_released = TRUE;
		return FALSE;
	case WM_MBUTTONUP:
		ctx->right_mouse_clicked = FALSE;
		ctx->left_mouse_pressed = FALSE;
		ctx->middle_mouse_released = TRUE;
		return FALSE;
	case WM_RBUTTONUP:
		ctx->right_mouse_clicked = FALSE;
		ctx->left_mouse_pressed = FALSE;
		ctx->right_mouse_released = TRUE;
		return FALSE;

	case WM_TIMER:
		if (wParam == RESIZE_TIMER)
		{
			// Resize has stopped, so reallocate the framebuffer
			KillTimer(hwnd, RESIZE_TIMER);

			RECT r;
			GetWindowRect(hwnd, &r);
			t_iv2 size = ivec2(r.right - r.left, r.bottom - r.top);
			win->size = size;
			win->w_root->size = size;

			free(win_int->buffers[0].data);
			free(win_int->buffers[1].data);
			_init_buffer(&win_int->buffers[0], size);
			_init_buffer(&win_int->buffers[1], size);
		}
		break;

	case WM_SIZE:;
		SetTimer(hwnd, RESIZE_TIMER, RESIZE_TIMER_DELAY, NULL);
		return FALSE;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

/*
Inits the main window class. Called only once in ftgr_new_window
*/
static inline ATOM _init_main_window_class(HINSTANCE hInstance)
{
	WNDCLASSEX wc = {0};
	wc.lpszClassName = FTGR_WINDOW_CLASS;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = windowProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	return RegisterClassEx(&wc);
}

static inline HWND _create_window(const_string title, t_iv2 size, HINSTANCE hInstance)
{
	return CreateWindowEx(
		0,					 // Extended window style
		FTGR_WINDOW_CLASS,	 // Class name
		title,				 // Window title
		WS_OVERLAPPEDWINDOW, // Window style
		CW_USEDEFAULT,		 // X position
		CW_USEDEFAULT,		 // Y position
		size.x,				 // Width
		size.y,				 // Height
		NULL,				 // Parent window
		NULL,				 // Menu
		hInstance,			 // Instance handle
		NULL				 // Additional application data
	);
}

static inline bool _init_buffer(t_ftgr_img *buffer, t_iv2 size)
{
	buffer->bpp = 4;
	buffer->size = size;
	buffer->line_size = size.x * 4;
	buffer->data_size = buffer->line_size * size.y;
	buffer->data = malloc(sizeof(U8) * buffer->data_size);
	ft_memset(buffer->data, 255, buffer->data_size);
	return !!(buffer->data);
}

t_ftgr_win *ftgr_new_window(t_ftgr_ctx *ctx, t_iv2 size, const_string title)
{
	t_ftgr_win *win = NULL;
	t_ftgr_win_int *win_int = NULL;
	t_list *lst;

	if (UNLIKELY((win = malloc(sizeof(t_ftgr_win))) == NULL) ||
		UNLIKELY((win_int = malloc(sizeof(t_ftgr_win_int))) == NULL))
	{
		_ftgr_error();
		free(win);
		return NULL;
	}

	ft_memset(win, 0, sizeof(t_ftgr_win));
	ft_memset(win_int, 0, sizeof(t_ftgr_win_int));

	win->ctx = ctx;
	win->internal = win_int;

	if (!ctx->main_window_class)
	{
		if (UNLIKELY((ctx->main_window_class = _init_main_window_class(ctx->instance_handle)) == 0))
			goto bad_window1;
	}
	if (UNLIKELY((win_int->window_handle = _create_window(title, size, ctx->instance_handle)) == NULL))
		goto bad_window1;

	int e = 0;
	ShowWindow(win_int->window_handle, SW_SHOWNORMAL);
	UpdateWindow(win_int->window_handle);
	if (
		UNLIKELY(SetPropW(win_int->window_handle, FTGR_PROP_NAME, win) == FALSE && (e = 1)) ||
		UNLIKELY((win_int->dc = GetDC(win_int->window_handle)) == NULL && (e = 2)) ||

		UNLIKELY((lst = ft_lstnew(win)) == NULL && (e = 3)) ||
		UNLIKELY((win->name = ft_strdup(title)) == NULL && (e = 4)) ||

		UNLIKELY(!_init_buffer(&win_int->buffers[0], size)) ||
		UNLIKELY(!_init_buffer(&win_int->buffers[1], size)))
		goto bad_window2;

	win_int->front = 0;
	win_int->back = 1;
	win->surface = &win_int->buffers[win_int->back];

	win->cursor_mode = FTGR_CURSOR_NORMAL;
	win->size = size;

	{
		win->w_root = ftgr_new_widget();
		if (UNLIKELY(win->w_root == NULL))
			goto bad_window2;
		win->w_root->name = "Window root";
		win->w_root->pos = ivec2(0, 0);
		win->w_root->size = size;
	}

	ft_lstadd_front(&ctx->windows, lst);
	ftgr_swap_buffers(win);
	return win;

bad_window1:
	_ftgr_error();
	free(win);
	free(win_int);
	return NULL;
bad_window2:
	_ftgr_error();
	ftgr_free_window(win);
	return NULL;
}

static bool cmp_window(void *a1, void *a2)
{
	return a1 == a2;
}

void ftgr_free_window(t_ftgr_win *win)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	if (win_int->window_handle)
	{
		int ret = DestroyWindow(win_int->window_handle);
		// Ne pas changer, documentation dis que on doit check explicitement pour TRUE/FALSE
		if (ret == FALSE)
			_ftgr_error();
		win_int->window_handle = NULL;
	}
	free(win_int->buffers[0].data);
	free(win_int->buffers[1].data);
	free(win_int);

	ft_lstremoveif(&win->ctx->windows, NULL, cmp_window, win);
	free(win);
}

void ftgr_bring_top(t_ftgr_win *win)
{
	(void)win;
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
	if (SetWindowTextA(FTGR_WINDOW_INT(win)->window_handle, win->name) == FALSE)
		_ftgr_error();
}

void ftgr_set_win_name_infos(t_ftgr_win *win, string infos)
{
	LIMIT_FREQ(1);
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "%s - %s", win->name, infos);
	if (SetWindowTextA(FTGR_WINDOW_INT(win)->window_handle, buffer) == FALSE)
		_ftgr_error();
}

/*
void ftgr_move_window(t_ftgr_win *win, t_iv2 pos)
{
	XMoveWindow(win->ctx->display, win->window, pos.x, pos.y);
}

void	ftgr_clear_window(t_ftgr_ctx *xvar, t_ftgr_win *win)
{
  XClearWindow(xvar->display, win->window);
  if (xvar->flush)
	XFlush(xvar->display);
}
*/

void ftgr_swap_buffers(t_ftgr_win *win)
{
	t_ftgr_win_int *win_int = FTGR_WINDOW_INT(win);

	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = win->size.x;
	bmi.bmiHeader.biHeight = -win->size.y; // Negative height to indicate top-down bitmap
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; // Assuming 32-bit RGBA pixel format
	bmi.bmiHeader.biCompression = BI_RGB;

	StretchDIBits(win_int->dc,
				  0, 0, win->size.x, win->size.y,
				  0, 0, win->size.x, win->size.y,
				  win->surface->data, &bmi,
				  0, SRCCOPY);

	win_int->front = !win_int->front;
	win_int->back = !win_int->back;
	win->surface = &win_int->buffers[win_int->back];
}

#endif
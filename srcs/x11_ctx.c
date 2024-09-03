/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_ctx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:46:04 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/02 03:14:40 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_x11_int.h"

#ifdef FT_OS_LINUX
#include "libft/time.h"
#include "libft/io.h"
#include <X11/Xproto.h>
#include <unistd.h>

static void ftgr_init_shm(t_ftgr_ctx *ctx);
// TODO: check return codes

static int error_handler(Display *display, XErrorEvent *event)
{
	static const string x_requests_str[] = {
		"XCreateWindow",
		"XChangeWindowAttributes",
		"XGetWindowAttributes",
		"XDestroyWindow",
		"XDestroySubwindows",
		"XChangeSaveSet",
		"XReparentWindow",
		"XMapWindow",
		"XMapSubwindows",
		"XUnmapWindow",
		"XUnmapSubwindows",
		"XConfigureWindow",
		"XCirculateWindow",
		"XGetGeometry",
		"XQueryTree",
		"XInternAtom",
		"XGetAtomName",
		"XChangeProperty",
		"XDeleteProperty",
		"XGetProperty",
		"XListProperties",
		"XSetSelectionOwner",
		"XGetSelectionOwner",
		"XConvertSelection",
		"XSendEvent",
		"XGrabPointer",
		"XUngrabPointer",
		"XGrabButton",
		"XUngrabButton",
		"XChangeActivePointerGrab",
		"XGrabKeyboard",
		"XUngrabKeyboard",
		"XGrabKey",
		"XUngrabKey",
		"XAllowEvents",
		"XGrabServer",
		"XUngrabServer",
		"XQueryPointer",
		"XGetMotionEvents",
		"XTranslateCoords",
		"XWarpPointer",
		"XSetInputFocus",
		"XGetInputFocus",
		"XQueryKeymap",
		"XOpenFont",
		"XCloseFont",
		"XQueryFont",
		"XQueryTextExtents",
		"XListFonts",
		"XListFontsWithInfo",
		"XSetFontPath",
		"XGetFontPath",
		"XCreatePixmap",
		"XFreePixmap",
		"XCreateGC",
		"XChangeGC",
		"XCopyGC",
		"XSetDashes",
		"XSetClipRectangles",
		"XFreeGC",
		"XClearArea",
		"XCopyArea",
		"XCopyPlane",
		"XPolyPoint",
		"XPolyLine",
		"XPolySegment",
		"XPolyRectangle",
		"XPolyArc",
		"XFillPoly",
		"XPolyFillRectangle",
		"XPolyFillArc",
		"XPutImage",
		"XGetImage",
		"XPolyText8",
		"XPolyText16",
		"XImageText8",
		"XImageText16",
		"XCreateColormap",
		"XFreeColormap",
		"XCopyColormapAndFree",
		"XInstallColormap",
		"XUninstallColormap",
		"XListInstalledColormaps",
		"XAllocColor",
		"XAllocNamedColor",
		"XAllocColorCells",
		"XAllocColorPlanes",
		"XFreeColors",
		"XStoreColors",
		"XStoreNamedColor",
		"XQueryColors",
		"XLookupColor",
		"XCreateCursor",
		"XCreateGlyphCursor",
		"XFreeCursor",
		"XRecolorCursor",
		"XQueryBestSize",
		"XQueryExtension",
		"XListExtensions",
		"XChangeKeyboardMapping",
		"XGetKeyboardMapping",
		"XChangeKeyboardControl",
		"XGetKeyboardControl",
		"XBell",
		"XChangePointerControl",
		"XGetPointerControl",
		"XSetScreenSaver",
		"XGetScreenSaver",
		"XChangeHosts",
		"XListHosts",
		"XSetAccessControl",
		"XSetCloseDownMode",
		"XKillClient",
		"XRotateProperties",
		"XForceScreenSaver",
		"XSetPointerMapping",
		"XGetPointerMapping",
		"XSetModifierMapping",
		"XGetModifierMapping",
		"XNoOperation",
	};

	static const string x_errors_str[] = {
		"Success",
		"BadRequest",
		"BadValue",
		"BadWindow",
		"BadPixmap",
		"BadAtom",
		"BadCursor",
		"BadFont",
		"BadMatch",
		"BadDrawable",
		"BadAccess",
		"BadAlloc",
		"BadColor",
		"BadGC",
		"BadIDChoice",
		"BadName",
		"BadLength",
		"BadImplementation",
	};

	ft_dprintf(ft_stderr, "X11 ERROR: ");
	if (event->error_code >= (sizeof(x_errors_str) / sizeof(x_errors_str[0])))
		ft_dprintf(ft_stderr, "code: %d(No error name available, minor code: %u) ", event->error_code, event->minor_code);
	else
		ft_dprintf(ft_stderr, "code: %s(%d, minor code: %u) ", x_errors_str[event->error_code], event->error_code, event->minor_code);

	if ((event->request_code - 1) >= (sizeof(x_requests_str) / sizeof(x_requests_str[0])))
		ft_dprintf(ft_stderr, "req: %d(No request name available) ", event->request_code);
	else
		ft_dprintf(ft_stderr, "req: %s ", x_requests_str[event->request_code - 1]);

	ft_dprintf(ft_stderr,
		"resoureid:%ld serial:%lu type:%d\n",
		event->resourceid,
		event->serial,
		event->type);
}

t_ftgr_ctx *ftgr_create_ctx()
{
	t_ftgr_ctx *ctx;

	ctx = malloc(sizeof(t_ftgr_ctx));
	if (!ctx)
		__FTRETURN_ERR(NULL, FT_EOMEM);

	ctx->display = XOpenDisplay("");
	if (ctx->display == 0)
	{
		free(ctx);
		__FTRETURN_ERR(NULL, FTGR_EX11);
	}

	XSetErrorHandler(error_handler);

	ctx->screen = DefaultScreen(ctx->display);
	ctx->root = DefaultRootWindow(ctx->display);
	ctx->cmap = DefaultColormap(ctx->display, ctx->screen);
	ctx->depth = DefaultDepth(ctx->display, ctx->screen);

	ctx->visual = DefaultVisual(ctx->display, ctx->screen);
	if (ctx->visual->class != TrueColor)
	{
		S32 nb_item;
		XVisualInfo template = (XVisualInfo){.class = TrueColor, .depth = ctx->depth};

		XVisualInfo *vi = XGetVisualInfo(ctx->display, VisualDepthMask | VisualClassMask, &template, &nb_item);
		if (!vi)
		{
			// TODO: CLEANUP
			// No truecolor
			XCloseDisplay(ctx->display);
			free(ctx);
			__FTRETURN_ERR(NULL, FTGR_EX11);
		}

		ctx->visual = vi->visual;
		ctx->cmap = XCreateColormap(ctx->display, ctx->root, ctx->visual, AllocNone);
	}

	ctx->flush = TRUE;
	ctx->windows = NULL;

	ctx->del_win_atom = XInternAtom(ctx->display, "WM_DELETE_WINDOW", False);
	ctx->protocols_atom = XInternAtom(ctx->display, "WM_PROTOCOLS", False);

	ftgr_init_shm(ctx);
	// ftgr_int_rgb_conversion(ctx);

	ft_clk_get(&ctx->global_time);
	ft_clk_get(&ctx->delta_time_clk);

	ctx->keys = NULL;
	return (ctx);
}

static void ftgr_init_shm(t_ftgr_ctx *ctx)
{
	S32 dummy;

	S32 use_pshm;
	char *dpy;
	char hostname[33];

	ctx->use_xshm = XShmQueryVersion(ctx->display, &dummy, &dummy, &use_pshm);

	if (ctx->use_xshm && use_pshm)
		ctx->pixmap_shm_format = XShmPixmapFormat(ctx->display);
	else
		ctx->pixmap_shm_format = -1;

	gethostname(hostname, 32);

	dpy = getenv("DISPLAY");
	if (dpy && ft_strlen(dpy) && *dpy != ':' && ft_strncmp(dpy, hostname, ft_strlen(hostname)) &&
		ft_strncmp(dpy, LOCALHOST, ft_strlen(LOCALHOST)))
	{
		ctx->pixmap_shm_format = -1;
		ctx->use_xshm = FALSE;
	}

	ctx->windows = NULL;
	if (!ctx->use_xshm)
		fprintf(stderr, "Warning: not using shared memory\n");
}

void ftgr_free(t_ftgr_ctx *ctx)
{
	t_list *win = ctx->windows;
	while (win)
	{
		t_list *nxt = win->next;
		ftgr_free_window(FTGR_WINDOW(win));
		free(win);
		win = nxt;
	}

	XFreeColormap(ctx->display, ctx->cmap);
	XDestroyWindow(ctx->display, ctx->root);
	XCloseDisplay(ctx->display);
	free(ctx);
}

#endif
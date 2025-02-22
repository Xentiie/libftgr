/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_ctx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:46:04 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/01 13:14:17 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_x11_int.h"

#ifdef FT_OS_LINUX
#include "libft/time.h"
#include "libft/io.h"

#include <X11/Xproto.h>

#include <unistd.h>

static bool ftgr_init_shm(t_ftgr_ctx *ctx);
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
	(void)display;

	ft_dprintf(ft_stderr, "X11 ERROR: ");
	if (event->error_code >= (sizeof(x_errors_str) / sizeof(x_errors_str[0])))
		ft_dprintf(ft_stderr, "code: %d(No error name available, minor code: %u) ", event->error_code, event->minor_code);
	else
		ft_dprintf(ft_stderr, "code: %s(%d, minor code: %u) ", x_errors_str[event->error_code], event->error_code, event->minor_code);

	if ((event->request_code - 1) >= (S64)(sizeof(x_requests_str) / sizeof(x_requests_str[0])))
		ft_dprintf(ft_stderr, "req: %d(No request name available) ", event->request_code);
	else
		ft_dprintf(ft_stderr, "req: %s ", x_requests_str[event->request_code - 1]);

	ft_dprintf(ft_stderr,
			   "resoureid:%ld serial:%lu type:%d\n",
			   event->resourceid,
			   event->serial,
			   event->type);

	return 0;
}

t_ftgr_ctx *ftgr_new_ctx()
{
	t_ftgr_ctx *ctx;
	XVisualInfo template;
	XVisualInfo *vi;
	S32 dummy;

	if (UNLIKELY((ctx = malloc(sizeof(t_ftgr_ctx))) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	ft_memset(ctx, 0, sizeof(t_ftgr_ctx));

	if ((ctx->display = XOpenDisplay("")) == NULL)
		goto exit_err;

	XSetErrorHandler(error_handler);

	ctx->screen = DefaultScreen(ctx->display);
	ctx->root = DefaultRootWindow(ctx->display);
	ctx->cmap = DefaultColormap(ctx->display, ctx->screen);
	ctx->depth = DefaultDepth(ctx->display, ctx->screen);

	ctx->visual = DefaultVisual(ctx->display, ctx->screen);
	if (ctx->visual->class != TrueColor)
	{
		template = (XVisualInfo){.class = TrueColor, .depth = ctx->depth};

		if ((vi = XGetVisualInfo(ctx->display, VisualDepthMask | VisualClassMask, &template, &dummy)) == NULL)
		{
			XCloseDisplay(ctx->display);
			goto exit_err;
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

	ft_bzero(ctx->keys, sizeof(ctx->keys));
	ft_bzero(ctx->mouse, sizeof(ctx->mouse));
	return (ctx);

exit_err:
	free(ctx);
	FT_RET_ERR(NULL, FT_ESYSCALL);
}

static bool ftgr_init_shm(t_ftgr_ctx *ctx)
{
	S32 use_pshm;
	S32 dummy;
	char *dpy;
	char hostname[33];

	ctx->use_xshm = XShmQueryVersion(ctx->display, &dummy, &dummy, &use_pshm);
	if (ctx->use_xshm && use_pshm)
	{
		ctx->pixmap_shm_format = XShmPixmapFormat(ctx->display);
		return TRUE;
	}

	if (gethostname(hostname, sizeof(hostname) - 1) == -1)
		goto exit_err;

	if ((dpy = getenv("DISPLAY")) != NULL								 /* DISPLAY exists in env */
		&& ft_strlen(dpy)												 /* DISPLAY is set to something */
		&& *dpy != ':' && ft_strncmp(dpy, hostname, ft_strlen(hostname)) /* DISPLAY n'est pas notre hostname */
		&& ft_strncmp(dpy, LOCALHOST, ft_strlen(LOCALHOST)))			 /* DISPLAY n'est pas localhost */
	{																	 /* -> pas de xshm */
		ctx->pixmap_shm_format = -1;
		ctx->use_xshm = FALSE;
	}

	if (!ctx->use_xshm)
		ft_fprintf(ft_fstderr, "warning: not using shared memory images\n");
exit_err:
	ctx->pixmap_shm_format = -1;
	ctx->use_xshm = FALSE;
	return FALSE;
}

void ftgr_destroy(t_ftgr_ctx *ctx)
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
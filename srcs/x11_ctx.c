/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_ctx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:46:04 by reclaire          #+#    #+#             */
/*   Updated: 2025/06/09 00:34:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftGFX_x11.h"

#if FT_OS_LINUX
#include "libft/time.h"
#include "libft/io.h"

#include <X11/Xproto.h>

#include <unistd.h>

static bool init_shm(struct s_ftGFX_ctx *ctx);
// TODO: check return codes

static S32 error_handler(Display *display, XErrorEvent *event)
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

	ft_fprintf(ft_fstderr, "X11 ERROR: ");
	if (event->error_code >= (sizeof(x_errors_str) / sizeof(x_errors_str[0])))
		ft_fprintf(ft_fstderr, "code: %d(No error name available, minor code: %u) ", event->error_code, event->minor_code);
	else
		ft_fprintf(ft_fstderr, "code: %s(%d, minor code: %u) ", x_errors_str[event->error_code], event->error_code, event->minor_code);

	if ((event->request_code - 1) >= (S64)(sizeof(x_requests_str) / sizeof(x_requests_str[0])))
		ft_fprintf(ft_fstderr, "req: %d(No request name available) ", event->request_code);
	else
		ft_fprintf(ft_fstderr, "req: %s ", x_requests_str[event->request_code - 1]);

	ft_fprintf(ft_fstderr,
			   "resoureid:%ld serial:%lu type:%d\n",
			   event->resourceid,
			   event->serial,
			   event->type);

	return 0;
}

static bool init_shm(struct s_ftGFX_ctx *ctx)
{
	struct s_ftGFX_ctx_private *private;
	S32 use_pshm;
	S32 dummy;
	char *dpy;
	char hostname[33];

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	private->use_xshm = XShmQueryVersion(private->display, &dummy, &dummy, &use_pshm);
	if (private->use_xshm && use_pshm)
	{
		private->pixmap_shm_format = XShmPixmapFormat(private->display);
		return TRUE;
	}

	if (gethostname(hostname, sizeof(hostname) - 1) == -1)
		goto exit_err;

	if ((dpy = getenv("DISPLAY")) != NULL								 /* DISPLAY exists in env */
		&& ft_strlen(dpy)												 /* DISPLAY is set to something */
		&& *dpy != ':' && ft_strncmp(dpy, hostname, ft_strlen(hostname)) /* DISPLAY n'est pas notre hostname */
		&& ft_strncmp(dpy, "localhost", 10))							 /* DISPLAY n'est pas localhost */
	{																	 /* -> pas de xshm */
		private->pixmap_shm_format = -1;
		private->use_xshm = FALSE;
	}

	if (!private->use_xshm)
		ft_fprintf(ft_fstderr, "warning: not using shared memory images\n");
	return TRUE;

exit_err:
	private->pixmap_shm_format = -1;
	private->use_xshm = FALSE;
	return FALSE;
}

struct s_ftGFX_ctx *ftGFX_create_ctx()
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_ctx *ctx;
	XVisualInfo template;
	XVisualInfo *vi;
	S32 dummy;

	if (UNLIKELY((ctx = malloc(sizeof(struct s_ftGFX_ctx) + sizeof(struct s_ftGFX_ctx_private))) == NULL))
		FT_RET_ERR(NULL, FT_EOMEM);
	private = (struct s_ftGFX_ctx_private *)ctx->private;

	if ((private->display = XOpenDisplay("")) == NULL)
		goto exit_einvop;

	XSetErrorHandler(error_handler);

	private->screen = DefaultScreen(private->display);
	private->root = DefaultRootWindow(private->display);
	private->cmap = DefaultColormap(private->display, private->screen);
	private->depth = DefaultDepth(private->display, private->screen);
	private->visual = DefaultVisual(private->display, private->screen);
	if (private->visual->class != TrueColor)
	{
		template = (XVisualInfo){
			.class = TrueColor,
			.depth = private->depth,
		};

		if ((vi = XGetVisualInfo(private->display, VisualDepthMask | VisualClassMask | VisualRedMaskMask | VisualGreenMaskMask | VisualBlueMaskMask, &template, &dummy)) == NULL)
		{
			ft_printf("no visuals found :(\n");
			XCloseDisplay(private->display);
			goto exit_einvop;
		}

		private->visual = vi->visual;
		private->cmap = XCreateColormap(private->display, private->root, private->visual, AllocNone);
	}

	private->del_win_atom = XInternAtom(private->display, "WM_DELETE_WINDOW", False);
	private->protocols_atom = XInternAtom(private->display, "WM_PROTOCOLS", False);

	private->flush = TRUE;
	ctx->windows = NULL;

	init_shm(ctx);

	ft_clk_get(&ctx->global_time);
	ft_clk_get(&ctx->delta_time_clk);
	ctx->delta_time = 0;

	ft_bzero(ctx->keys, sizeof(ctx->keys));
	ft_bzero(ctx->mouse, sizeof(ctx->mouse));
	ctx->keys_char[0] = '\0';

	ctx->should_close = FALSE;

	return ctx;

exit_einvop:
	free(ctx);
	FT_RET_ERR(NULL, FT_EINVOP);
}

void ftGFX_destroy_ctx(struct s_ftGFX_ctx *ctx)
{
	struct s_ftGFX_ctx_private *private;
	struct s_ftGFX_window *win;
	struct s_ftGFX_window *next;

	private = (struct s_ftGFX_ctx_private *)ctx->private;

	win = ctx->windows;
	while (win)
	{
		next = win->next;
		ftGFX_destroy_window(win);
		win = next;
	}

	XFreeColormap(private->display, private->cmap);
	XDestroyWindow(private->display, private->root);
	XCloseDisplay(private->display);
	free(ctx);
}

#endif
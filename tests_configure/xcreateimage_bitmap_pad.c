/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcreateimage_bitmap_pad.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:28:14 by reclaire          #+#    #+#             */
/*   Updated: 2024/04/22 20:35:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xlib.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef PADN
#define PADN 8
#endif

#ifndef WIDTH
# define WIDTH 300
#endif

#ifndef HEIGHT
# define HEIGHT 300
#endif

int main()
{
    Display *display = XOpenDisplay("");
    int screen = DefaultScreen(display);
    int depth = DefaultDepth(display, screen);
    int cmap = DefaultColormap(display, screen);
    Window root = DefaultRootWindow(display);
    Visual *visual = DefaultVisual(display, screen);

    XSetWindowAttributes xswa = (XSetWindowAttributes){
        .background_pixel = 0,
        .border_pixel = -1,
        .colormap = cmap,
        .event_mask = 0xFFFFFF};
    unsigned long win_valuemask = CWEventMask | CWBackPixel | CWBorderPixel | CWColormap;
    Window window = XCreateWindow(display, root,
                                    0, 0, WIDTH, HEIGHT,
                                    0, CopyFromParent, InputOutput, visual,
                                    win_valuemask, &xswa);
    XMapRaised(display, window);
	XEvent ev;
	XWindowEvent(display, window, ExposureMask, &ev);
	XPutBackEvent(display, &ev);


    GC gc = XCreateGC(display, window, 0, NULL);

    int width = WIDTH;
    int height = HEIGHT;

    for (int i = 0; i < 1000; i++)
    {
        char *data = malloc(sizeof(char) * (width + 32) * height * 4);
        XImage *img = XCreateImage(display, visual, depth, XYPixmap, 0, data, width, height, PADN, 0);
        for (int j = 0; j < (width + 32) * height * 4; j++)
            data[j] = (j+i) * j % 255;

        XPutImage(display, window, gc, img, 0, 0, 0, 0, WIDTH, HEIGHT);
        XFlush(display);
        XSync(display, 0);
    }
}

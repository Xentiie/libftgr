#include <X11/Xlib.h>
#include <X11/Xcursor/Xcursor.h>
#include <stdio.h>

int main(void) {
	Display *dpy = XOpenDisplay(NULL);
	if (!dpy) {
		fprintf(stderr, "Failed to open display\n");
		return 1;
	}

	// Load images for a named cursor from the theme
	XcursorImages *images = XcursorLibraryLoadImages("hand1", dpy, 10);
	if (!images) {
		fprintf(stderr, "Failed to load cursor images\n");
		XCloseDisplay(dpy);
		return 1;
	}

	// Create a Cursor from the images
	Cursor cursor = XcursorImagesLoadCursor(dpy, images);

	// Free the images now that the Cursor is created
	XcursorImagesDestroy(images);

	// Use the cursor in some way if needed...
	// (you could attach it to a window, etc.)

	// Free the Cursor when done
	XFreeCursor(dpy, cursor);
	XCloseDisplay(dpy);

	return 0;
}

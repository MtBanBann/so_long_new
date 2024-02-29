#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>

int main() {
    Display *display;
    XEvent event;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Error: Could not open display\n");
        return 1;
    }

    printf("Press a key (ESC to quit)...\n");

    while(1) {
        XNextEvent(display, &event);

        if (event.type == KeyPress) {
            char keybuf[32];
            KeySym keysym;
            XLookupString(&event.xkey, keybuf, sizeof(keybuf), &keysym, NULL);
            printf("Key pressed: %s\n", XKeysymToString(keysym));

            if (keysym == XK_Escape) // ESC key
                break;
        }
    }

    XCloseDisplay(display);
    return 0;
}
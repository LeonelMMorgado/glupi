#include <window.h>
#include <time.h>
#include <gl_util.h>
#include <stdlib.h>

Window *window_create(WinSettings settings) {
    Window *window = malloc(sizeof(Window));
    window->window = initGL(settings);
    return window;
}

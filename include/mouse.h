#ifndef _MOUSE_H
#define _MOUSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <button.h>
#include <vmm/ivec2.h>
#include <window.h>

typedef struct _mouse {
    Button buttons[GLFW_MOUSE_BUTTON_LAST];
    IVector2 position, delta;
} Mouse;

void mouse_set_grabbed(Window *window, bool grabbed);
bool mouse_get_grabbed(Window *window);

#endif


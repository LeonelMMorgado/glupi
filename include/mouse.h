#ifndef _MOUSE_H
#define _MOUSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <button.h>
#include <vmm/vec2.h>

typedef struct _mouse {
    Button buttons[GLFW_MOUSE_BUTTON_LAST];
    Vector2 position, delta;
} Mouse;

void mouse_set_grabbed(Mouse mouse, bool grabbed);
bool mouse_get_grabbed(Mouse mouse);

#endif


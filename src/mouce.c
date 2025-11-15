#include <mouse.h>

void mouse_set_grabbed(Window *window, bool grabbed) {
    glfwSetInputMode(window->window, GLFW_CURSOR, grabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool mouse_get_grabbed(Window *window) {
    return glfwGetInputMode(window->window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

#include <window.h>
#include <stdlib.h>
#include <time.h>
#include <gl_util.h>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void _framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    Window *win = glfwGetWindowUserPointer(window);
    win->settings.size.x = width;
    win->settings.size.y = height;
}

void _key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(key < 0) return;

    Window *win = glfwGetWindowUserPointer(window);
    
    switch(action) {
    case GLFW_PRESS:
        win->keyboard_keys[key].down = true;
        break;
    case GLFW_RELEASE:
        win->keyboard_keys[key].down = false;
        break;
    default:
        break;
    }
}

void _cursor_callback(GLFWwindow *window, double xpos, double ypos) {
    Window *win = glfwGetWindowUserPointer(window);
    Vector2 mouse_pos = vec2_float(xpos, ypos);
    win->mouse.delta = vec2_sub(mouse_pos, win->mouse.position);
    win->mouse.position = mouse_pos;
}

void _mouse_callback(GLFWwindow *window, int button, int action, int mods) {
    if(button < 0) return;

    Window *win = glfwGetWindowUserPointer(window);
    
    switch(action) {
    case GLFW_PRESS:
        win->mouse.buttons[button].down = true;
        break;
    case GLFW_RELEASE:
        win->mouse.buttons[button].down = false;
        break;
    default:
        break;
    }
}

void _scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    Window *win = glfwGetWindowUserPointer(window);

    win->mouse.scroll_delta = yoffset;
}

Window *window_create(WinSettings settings) {
    Window *window = malloc(sizeof(Window));
    window->window = initGL(settings);
    glfwSetWindowUserPointer(window->window, window);

    glfwSetFramebufferSizeCallback(window->window, _framebuffer_size_callback);
    glfwSetKeyCallback(window->window, _key_callback);
    glfwSetCursorPosCallback(window->window, _cursor_callback);
    glfwSetMouseButtonCallback(window->window, _mouse_callback);
    glfwSetScrollCallback(window->window, _scroll_callback);

    return window;
}

void mouse_set_grabbed(Window *window, bool grabbed) {
    glfwSetInputMode(window->window, GLFW_CURSOR,  grabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool mouse_get_grabbed(Window *window) {
    return glfwGetInputMode(window->window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void window_destroy(Window **window) {
    if(!window) return;
    if(!*window) return;
    glfwDestroyWindow((*window)->window);
    free(*window);
    *window = NULL;
}

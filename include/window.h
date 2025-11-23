#ifndef _WINDOW_H
#define _WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vmm/vec2.h>
#include <stdbool.h>
#include <button.h>
#include <mouse.h>

typedef struct _win_set {
    char *name;
    bool inv_border;
    bool inv_bg;
    Vector2 size;
} WinSettings;

typedef struct _window {
    GLFWwindow *window;

    Mouse mouse;
    Button keyboard_keys[GLFW_KEY_LAST];

    WinSettings settings;
} Window;

Window *window_create(WinSettings settings);
void mouse_set_grabbed(Window *window, bool grabbed);
bool mouse_get_grabbed(Window *window);
void window_destroy(Window **window);

#endif


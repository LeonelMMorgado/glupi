#ifndef _STATE_H
#define _STATE_H

#include <button.h>
#include <mouse.h>
#include <window.h>
#include <renderer.h>

typedef struct _state State;
typedef void (*func_state)(State *);

struct _state {
    Window *window;
    Renderer *renderer;

    func_state init, tick, update, render, destroy;

    func_state mouse_func;
    func_state scroll_func;
    func_state mouse_button_funcs[GLFW_MOUSE_BUTTON_LAST];
    func_state keyboard_funcs[GLFW_KEY_LAST];

    uint64_t last_second, frames, fps, last_frame, frame_delta, ticks, tps, tick_remainder;
    float now, last_time, delta_time;
};

State *state_create(Window *window, Renderer *renderer, func_state init, func_state tick, func_state update, func_state render, func_state destroy);
void state_loop(State *state);
void state_update_time(State *state);
void state_process_input(State *state);
void state_assign_mouse_func(State *state, func_state mouse_function);
void state_assign_scroll_func(State *state, func_state scroll_function);
void state_assign_mouse_button_func(State *state, func_state button_function, GLenum button);
void state_assign_key_func(State *state, func_state key_function, GLenum key);
void state_destroy(State **state);

#endif


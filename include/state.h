#ifndef _STATE_H
#define _STATE_H

#include <button.h>
#include <mouse.h>
#include <window.h>

typedef struct _state State;
typedef void (*func_state)(struct _state *);

struct _state {
    Window *window;

    func_state init, tick, update, render, destroy;

    Mouse mouse;
    Button keyboard_keys[GLFW_KEY_LAST];

    uint64_t last_second, frames, fps, last_frame, frame_delta, ticks, tps, tick_remainder;
    
};

State *state_init(Window *window, func_state init, func_state tick, func_state update, func_state render, func_state destroy);
void state_loop(State *state);

#endif

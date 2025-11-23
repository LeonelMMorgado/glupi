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

    uint64_t last_second, frames, fps, last_frame, frame_delta, ticks, tps, tick_remainder;
    float now, last_time, delta_time;
};

State *state_create(Window *window, Renderer *renderer, func_state init, func_state tick, func_state update, func_state render, func_state destroy);
void state_loop(State *state);
void state_destroy(State **state);

#endif


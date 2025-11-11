#include <state.h>
#include <stdlib.h>

State *state_init(Window *window, Renderer *renderer, func_state init, func_state tick, func_state update, func_state render, func_state destroy) {
    State *state = malloc(sizeof(State));
    state->init = init;
    state->destroy = destroy;
    state->tick = tick;
    state->update = update;
    state->render = render;
    state->window = window;
    state->renderer = renderer;
    return state;
}

void state_loop(State *state) {
    state->init(state);
    while(!glfwWindowShouldClose(state->window->window)) {
        state->tick(state);
        state->update(state);
        state->render(state);
    }
    state->destroy(state);
}

void state_delete(State *state) {
    window_delete(state->window);
    renderer_delete(state->renderer);
    free(state);
}

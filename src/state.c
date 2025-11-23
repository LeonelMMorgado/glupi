#include <state.h>

State *state_create(Window *window, Renderer *renderer, func_state init, func_state tick, func_state update, func_state render, func_state destroy) {
    State *state = calloc(1, sizeof(State));
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

void state_update_time(State *state) {
    state->now = glfwGetTime();
    state->delta_time = state->now - state->last_time;
    state->last_time = state->now;
}

void state_process_input(State *state) {
    glfwPollEvents();

    if(!vec2_equal_vec(state->window->mouse.delta, vec2_zero()))
        if(state->mouse_func) state->mouse_func(state);

    if(state->window->mouse.scroll_delta != 0.0) //threshold?
        if(state->scroll_func) state->scroll_func(state);
    
    for(int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
        if(state->window->mouse.buttons[i].pressed)
            if(state->mouse_button_funcs[i]) state->mouse_button_funcs[i](state);

    for(int i = 0; i < GLFW_KEY_LAST; i++)
        if(state->window->keyboard_keys[i].pressed)
            if(state->keyboard_funcs[i]) state->keyboard_funcs[i](state);
}

void state_assign_mouse_func(State *state, func_state mouse_function) {
    if(!state || !mouse_function) return;
    state->mouse_func = mouse_function;
}

void state_assign_scroll_func(State *state, func_state scroll_function) {
    if(!state || !scroll_function) return;
    state->scroll_func = scroll_function;
}

void state_assign_mouse_button_func(State *state, func_state button_function, GLenum button) {
    if(!state || !button_function) return;
    state->mouse_button_funcs[button] = button_function;
}

void state_assign_key_func(State *state, func_state key_function, GLenum key) {
    if(!state || !key_function) return;
    state->keyboard_funcs[key] = key_function;
}

void state_destroy(State **state) {
    if(!state) return;
    if(!*state) return;
    if((*state)->window) window_destroy(&((*state)->window));
    if((*state)->renderer) renderer_destroy(&((*state)->renderer));
    free(*state);
    *state = NULL;
}

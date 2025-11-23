#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <gl_util.h>
#include <shader.h>
#include <state.h>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

void mouse_movement(State *state) {
    camera_yaw_pitch(state->renderer->camera, state->window->mouse.delta);
}

void scroll(State *state) {
    camera_update_fov(state->renderer->camera, state->renderer->camera->camera_p.fov + state->window->mouse.scroll_delta);
}

void w_key(State *state) {
    camera_move(state->renderer->camera, vec3_scalar_mul(vec3_forward(), state->delta_time));
}

void a_key(State *state) {
    camera_move(state->renderer->camera, vec3_scalar_mul(vec3_left(), state->delta_time));
}

void s_key(State *state) {
    camera_move(state->renderer->camera, vec3_scalar_mul(vec3_back(), state->delta_time));
}

void d_key(State *state) {
    camera_move(state->renderer->camera, vec3_scalar_mul(vec3_right(), state->delta_time));
}

void space_key(State *state) {
    camera_move(state->renderer->camera, vec3_scalar_mul(vec3_up(), state->delta_time));
}

void shift_key(State *state) {
    camera_move(state->renderer->camera, vec3_scalar_mul(vec3_down(), state->delta_time));
}

void init(State *state) {
    mouse_set_grabbed(state->window, true);

    state_assign_mouse_func(state, &mouse_movement);
    state_assign_scroll_func(state, &scroll);
    state_assign_key_func(state, &w_key, GLFW_KEY_W);
    state_assign_key_func(state, &a_key, GLFW_KEY_A);
    state_assign_key_func(state, &s_key, GLFW_KEY_S);
    state_assign_key_func(state, &d_key, GLFW_KEY_D);
    state_assign_key_func(state, &space_key, GLFW_KEY_SPACE);
    state_assign_key_func(state, &shift_key, GLFW_KEY_LEFT_SHIFT);

    shader_use(state->renderer->shader);
}

void tick(State *state) {
    state_process_input(state);
    camera_update_view_proj(state->renderer->camera);
}

void update(State *state) {
    state_update_time(state);
    printf("FPS: %.2f\n", 1.0 / state->delta_time);
}

void render(State *state) {
    renderer_clear(state->renderer);
    renderer_view_proj(state->renderer);
    glfwSwapBuffers(state->window->window);
}

void destroy(State *state) {
    glfwTerminate();
}

int main(void) {
    Window *win = NULL;
    Camera *camera = NULL;
    Shader *shader = NULL;
    Renderer *renderer = NULL;
    State *state = NULL;

    WinSettings settings = (WinSettings){
        .name = "Hello World!",
        .inv_bg = false,
        .inv_border = false,
        .size = vec2_float(SCR_WIDTH, SCR_HEIGHT)
    };
    win = window_create(settings);
    if(!win) goto cleanup;

    Camera_Args cam_arg;
    cam_arg.p_fov = 90;
    camera = camera_create(win, PERSPECTIVE_CAMERA, cam_arg);
    shader = shader_create("shaders/vertex.glsl", "shaders/fragment.glsl");
    if(!camera || !shader) goto cleanup;

    renderer = renderer_create(camera, shader, COLOR_WHITEA);
    state = state_create(win, renderer, &init, &tick, &update, &render, &destroy);
    if(!renderer || !state) goto cleanup;

    state_loop(state);
    state_destroy(&state);

    return 0;

cleanup:
    if(win) window_destroy(&win);
    if(camera) camera_destroy(&camera);
    if(shader) shader_destroy(&shader);
    if(renderer) renderer_destroy(&renderer);
    if(state) state_destroy(&state);
    return 1;
}


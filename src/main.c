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

void init(State *state) {
    mouse_set_grabbed(state->window, true);

}

void tick(State *state) {

}

void update(State *state) {

}

void render(State *state) {

}

void destroy(State *state) {
    //deallocate all resources
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

    renderer = renderer_create(camera, shader, COLOR_BLACKA);
    state = state_create(win, &init, &tick, &update, &render, &destroy);
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


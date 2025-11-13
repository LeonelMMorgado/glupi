#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <gl_util.h>
#include <input.h>
#include <shader.h>
#include <state.h>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

GLuint compute_program;
float now, last_time;

void init(State *state) {
    GLuint compute_shader = make_shader("shaders/compute.glsl", GL_COMPUTE_SHADER);
    compute_program = glCreateProgram();
    glAttachShader(compute_program, compute_shader);
    glLinkProgram(compute_program); //FIXME: check err

    last_time = 0;
}

void tick(State *state) {
    //TODO: HERE for input
    process_input(state->window->window);
    return;
}

void update(State *state) {
    now = (float)glfwGetTime();
    printf("FPS: %f\n", 1.0f / (now - last_time));
    last_time = now;
}

void render(State *state) {
    glUseProgram(compute_program);
    //Vincular recursos
    glBindImageTexture(0, outputTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, ssbo_voxels);
    // Dispara as threads do compute shader.
    //  Dividimos o tamanho da tela pelo tamanho do grupo de trabalho definido no shader.
    //  Se o tamanho do grupo for 8x8, por exemplo:
    glDispatchCompute(SCR_WIDTH / 8, SCR_HEIGHT / 8, 1);

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    // Desenhar o quad na tela
    int width, height;
    glfwGetFramebufferSize(state->window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_use(state->renderer->shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, outputTexture);

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(state->window->window);
    glfwPollEvents();
}

void destroy(State *state) {
    //deallocate all resources
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadEBO);
    glDeleteBuffers(1, &ssbo_voxels);
    gldeleteTextures(1, &outputTexture);
    glDeleteProgram(compute_program);
    state_delete(&state);
    glfwTerminate();
}

int main(void) {
    Window *win = NULL;
    Camera *main_cam = NULL;
    Shader *main_shader = NULL;
    Renderer *renderer = NULL;
    State *state = NULL;
    
    WinSettings settings = (WinSettings){
        .name = "Hello World!",
        .inv_border = false,
        .inv_bg = false,
        .size = vec2_float(SCR_WIDTH, SCR_HEIGHT)
    };
    win = window_create(settings);
    if(!win->window) goto main_clean;
    
    Camera_Args cam_arg;
    cam_arg.p_fov = 90;
    main_cam = camera_create(win, PERSPECTIVE_CAMERA, cam_arg);
    main_shader = shader_create("shaders/vert.glsl", "shaders/frag.glsl");
    if(!main_cam || !main_shader) goto main_clean;
    renderer = renderer_create(main_cam, main_shader, vec4_one());
    if(!renderer) goto main_clean;
    
    state = state_create(win, renderer, &init, &tick, &update, &render, &destroy);
    if(!state) goto main_clean;
    state_loop(state);
    return 0;

main_clean:
    if(win) window_delete(&win);
    if(main_cam) camera_delete(&main_cam);
    if(main_shader) shader_delete(&main_shader);
    if(renderer) renderer_delete(&renderer);
    if(state) state_delete(&state);
    return -1;
}

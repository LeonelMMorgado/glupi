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

// int main(void) {
//     
//     // GLFWwindow *window = initGL("Hello World", false);
//     // if(!window) return -1;
// 
//     // build and compile our shader program
//     // ------------------------------------
//     Shader program = create_shader("shaders/vertex.glsl", "shaders/fragment.glsl");
//     if(!program) {
//         printf("Stopping execution after shader program error\n");
//         return -1;
//     }
//     glUseProgram(program);
// 
//     // render loop
//     // -----------
//     // while (!glfwWindowShouldClose(window)) {
//         // input
//         //=
//         processInput(window/*, program*/);
//         
//         // render
//         //=
//         glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
//         glClear(GL_COLOR_BUFFER_BIT);
//         // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//         // -------------------------------------------------------------------------------
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     // }
// 
//     // de-allocate all resources once they've outlived their purpose:
//     // ------------------------------------------------------------------------
//     glDeleteProgram(program);
// 
//     // glfw: terminate, clearing all previously allocated GLFW resources.
//     // ------------------------------------------------------------------
//     // glfwTerminate();
//     // return 0;
// }

void init(State *state) {
    shader_use(state->renderer->shader);
}

void tick(State *state) {
    return;
}

void update(State *state) {
    process_input(state->window->window);
}

void render(State *state) {
    glClearColor(01,01,01,01);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(state->window->window);
    glfwPollEvents();
}

void destroy(State *state) {
    //deallocate all resources
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

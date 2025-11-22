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

int main(void) {
    
    // GLFWwindow *window = initGL("Hello World", false);
    // if(!window) return -1;

    // build and compile our shader program
    // ------------------------------------
    Shader program = create_shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    if(!program) {
        printf("Stopping execution after shader program error\n");
        return -1;
    }
    glUseProgram(program);

    // render loop
    // -----------
    // while (!glfwWindowShouldClose(window)) {
        // input
        //=
        processInput(window/*, program*/);
        
        // render
        //=
        glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    // }

    // de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteProgram(program);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    // glfwTerminate();
    // return 0;
}

void init(State *state) {

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
    WinSettings settings = {
        .inv_bg = false,
        .inv_border = false,
        .name = "Hello World!",
        .size = {SCR_WIDTH, SCR_HEIGHT}
    };
    Window *win = window_create(settings);
    if(!win) return -1;
    State state = state_init(&win, &init, &tick, &update, &render, &destroy);
    state_loop(&state);
}

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <window.h>

GLFWwindow *initGL(WinSettings settings) {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();

    if(settings.inv_bg)
        glfwInitHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(settings.size.x, settings.size.y, settings.name, NULL, NULL);
    if (!window)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    if(settings.inv_border)
        glfwSetWindowAttrib(window, GLFW_DECORATED, GL_TRUE);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        glfwTerminate();
        return NULL;
    }
    return window;
}


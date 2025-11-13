#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <window.h>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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


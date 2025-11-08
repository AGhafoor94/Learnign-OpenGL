#include <stdio.h>
#include <glad/glad.h>
// GLFW (include after glad)
// -mwindows
#include <GLFW/glfw3.h>


int main() {
    const int WIDTH = 500;
    const int HEIGHT = 500;
    glfwInit();
    // need to tell GLFW hints at what version we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 2 versions, core and core & compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* glfw_window = glfwCreateWindow(WIDTH, HEIGHT, "FIRST Project", NULL, NULL);

    // error handling for window failing to generate
    if (glfw_window == NULL) {
        printf("Failed to create window");
        glfwTerminate();
        return -1;
    }

    // now to tell glfw to use window
    glfwMakeContextCurrent(glfw_window);

    // Using glad to load opengl
    gladLoadGL();

    // Using current viewport of the window for OpenGL to use
    glViewport(0, 0, WIDTH, HEIGHT);

    // Clear buffer, this is the back buffer which will need to be sent to front buffer
    glClearColor(0.7f, 0.3f, 0.17f, 1.0f);

    // using this command to clear buffer and for OpenGL to use
    glClear(GL_COLOR_BUFFER_BIT);

    // swap back buffer with front buffer
    glfwSwapBuffers(glfw_window);

    while (!glfwWindowShouldClose(glfw_window)) {
        // poll messages
        glfwPollEvents();
    }

    glfwDestroyWindow(glfw_window);
    glfwTerminate();

    return 0;
}
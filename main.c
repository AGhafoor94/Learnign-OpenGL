#include <stdio.h>
#include <glad/glad.h>
// GLFW (include after glad)
// -mwindows
#include <GLFW/glfw3.h>


int main() {
    const int WIDTH = 500;
    const int HEIGHT = 500;
    const char* vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 a_pos;\n"
        "void main(){\n"
        "gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);\n"
        "}\0";
    const char* fragment_shader_source = "#version 330 core\n"
        "out vec4 frag_colour;\n"
        "void main() {\n"
        "frag_colour = vec4(0.8f, 0.3f,0.02f,1.0f);\n"
        "}\n\0";
    glfwInit();
    // need to tell GLFW hints at what version we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 2 versions, core and core & compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // open gl floats
    // 2D
    // float(sqrt(3)) = 1.73205080757f
    // every 3 floats = 1 coordinate
    // left corner, right corner and then top corner
    GLfloat verticies[] = {
        -0.5f, -0.5f * 1.73205080757f / 3, 0.0f,
        0.5f, 0.5f * 1.73205080757f / 3, 0.0f,
        0.0f, 0.5f * 1.73205080757f * 2 / 3, 0.0f,
    };
    // Shaders are opengl objects and can only be accessed by referencing a value

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

    // Reference to store our vertex shader in
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    // gl shader source: reference value, 1 stream, source code
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    // need to compile into machine code for GPU
    glCompileShader(vertex_shader);


    // Now same for the fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    // gl shader source: reference value, 1 stream, source code
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    // need to compile into machine code for GPU
    glCompileShader(fragment_shader);

    // now to use these shaders, need to wrap up into a shader program
    GLuint shader_program = glCreateProgram();
    // attach shaders to the program
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    // link shaders
    glLinkProgram(shader_program);

    glDeleteShaders(vertex_shader);
    glDeleteShaders(fragment_shader);

    // now to tell opengl how to interpret them
    // need to send in batches of data from cpu to gpu

    GLuint v_a_o;
    GLuint v_b_o;
    // generate VAO BEFORE VBO
    glGenVertexArrays(1, &v_a_o);
    // only have 1 3d object currently
    glGenBuffers(1, &v_b_o);

    // Binding: makes a certain object the current object. 
    // bind VAO to use it
    glBindVertexArray(v_a_o);
    
    // we're using an array of buffers
    glBindBuffer(GL_ARRAY_BUFFER, v_b_o);

    // now to store in memory buffer
    // specify use of data: stream (modified once and used one time), static (modified once but used many times), dynamic (modified multiple times and used multiple times)
    // Draw: image modifed, Read and Static
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    // vertex array object (VAO) stores pointers to one or more VBOs and tells opengl how to interpret them, lets you switch quickly between VBOs


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
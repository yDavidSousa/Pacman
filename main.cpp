#include "include/shader.h"
#include "include/mesh.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define GL_SILENCE_DEPRECATION

const unsigned int SCR_WIDTH = 512;
const unsigned int SCR_HEIGHT = 640;

const char *fragment_shader_src = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
const char *vertex_shader_src = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

int main(int argc, char** argv)
{
    GLFWwindow* window;

    if(glfwInit() == false)
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
    std::cout << "I'm apple machine" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Pacman", NULL, NULL);
    if(window == false)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(glewInit())
    {
        return -1;
    }

    //glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    shader test_shader;
    test_shader.create(vertex_shader_src, fragment_shader_src);
    test_shader.link();

    // Set up vertex data (and buffer(s)) and attribute pointers
    const float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };
    const unsigned int triangles[] = {
        0, 1, 3,
        1, 2, 3
    };
    mesh quad_mesh(vertices, triangles);
    quad_mesh.bind_layout();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while(glfwWindowShouldClose(window) == false)
    {
        // time
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        test_shader.bind();
        quad_mesh.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    quad_mesh.~mesh();
    test_shader.~shader();

    glfwTerminate();

    return 0;
}

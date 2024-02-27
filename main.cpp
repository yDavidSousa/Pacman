#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "mesh.h"
#include "shader.h"

#define GL_SILENCE_DEPRECATION

const unsigned int SCR_WIDTH = 512;
const unsigned int SCR_HEIGHT = 640;

const char *fragment_shader_src = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
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
#ifdef __APPLE__
    std::cout << "I'm apple machine" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Pacman", NULL, NULL);
    if(window == NULL)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        return -1;
    }

    const std::vector<float> vb_data = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    mesh triangle_mesh(vb_data);
    triangle_mesh.bind();

    shader standard_shader = shader();
    standard_shader.create(vertex_shader_src, fragment_shader_src);
    standard_shader.link();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while(glfwWindowShouldClose(window) == false)
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT);

        standard_shader.bind();
        triangle_mesh.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    standard_shader.~shader();

    glfwTerminate();

    return 0;
}

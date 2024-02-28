#define GL_SILENCE_DEPRECATION

#include "gl_renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

const unsigned int SCR_WIDTH = 512;
const unsigned int SCR_HEIGHT = 640;

const char *vertex_shader_src = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "\n"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\0";
const char *fragment_shader_src = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"
    "\n"
    "uniform sampler2D texture1;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture(texture1, TexCoord);\n"
    "}\n\0";

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

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    gl_renderer renderer;

    auto standard_shader = renderer.create_shader();
    standard_shader->create(vertex_shader_src, fragment_shader_src);
    standard_shader->link();

    auto quad_mesh = renderer.create_mesh();
    quad_mesh->set_vertices(quad_vertices);
    quad_mesh->set_indices(quad_indices);
    quad_mesh->bind();

    auto texture = renderer.create_texture();
    texture->set_info();
    int width, height, nrChannels;
    unsigned char *data = stbi_load("/Users/davidsousa/Documents/projects/pacman/resources/wall.jpg", &width, &height, &nrChannels, 0);
    if(data)
    {
        texture->set_data(width, height, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while(glfwWindowShouldClose(window) == false)
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT);

        texture->bind();
        standard_shader->bind();
        quad_mesh->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

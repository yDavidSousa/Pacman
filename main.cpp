#define GL_SILENCE_DEPRECATION

#include "src/include/gl_renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

const unsigned int SCR_WIDTH = 512;
const unsigned int SCR_HEIGHT = 640;

float window_width = SCR_WIDTH;
float window_height = SCR_HEIGHT;

const char *vertex_shader_src = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "\n"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 camera_position   = glm::vec3(0.0f, 0.0f, 0.0f);

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

    const float target_width = static_cast<float>(SCR_WIDTH);
    const float target_height = static_cast<float>(SCR_HEIGHT);
    float target_aspect = target_height / target_width;

    while(glfwWindowShouldClose(window) == false)
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        texture->bind();
        standard_shader->bind();

        glm::mat4 projection = glm::mat4(1.0f);

        float window_aspect = window_width / window_height;
        if(window_aspect >= target_aspect)
        {
            projection = glm::ortho(-window_aspect, window_aspect, -1.0f, 1.0f, -1.0f, 1.0f);
        } 
        else
        { 
            projection = glm::ortho(-1.0f, 1.0f, -target_aspect, target_aspect, -1.0f, 1.0f);
        }

        standard_shader->set_uniform_mat4("projection", projection);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, camera_position);
        standard_shader->set_uniform_mat4("view", view);
    
        glm::mat4 model = glm::mat4(1.0f);
        standard_shader->set_uniform_mat4("model", model);
    
        quad_mesh->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_position += cameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_position -= cameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_position -= cameraSpeed * glm::vec3(-1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_position += cameraSpeed * glm::vec3(-1.0f, 0.0f, 0.0f);
}
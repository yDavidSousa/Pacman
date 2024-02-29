#define GL_SILENCE_DEPRECATION

#include "src/include/gl_renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

const unsigned int SCALE = 3;

const unsigned int PIXELS_TILE = 8;

const unsigned int SCR_WIDTH = 224 * SCALE;
const unsigned int SCR_HEIGHT = 288 * SCALE;

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

    auto mockup_texture = renderer.create_texture();
    mockup_texture->set_info();
    load_texture("/Users/davidsousa/Documents/projects/pacman/resources/mockup.png", false, mockup_texture);

    auto pacman_texture = renderer.create_texture();
    pacman_texture->set_info();
    load_texture("/Users/davidsousa/Documents/projects/pacman/resources/pacman.png", true, pacman_texture);

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

        mockup_texture->bind();
        standard_shader->bind();

        glm::mat4 projection = glm::mat4(1.0f);
        float window_aspect = window_width / window_height;
        float h = window_height / target_height;
        float w = window_width / target_width;

        glm::vec2 viewport = glm::vec2(1, 1);
        if(window_aspect >= target_aspect)
        {
            projection = glm::ortho(-window_aspect, window_aspect, -1.0f, 1.0f, -1.0f, 1.0f);
            viewport = glm::vec2((window_aspect + target_aspect) - 2.0f, 1);
        } 
        else
        {
            projection = glm::ortho(-1.0f, 1.0f, -target_aspect, target_aspect, -1.0f, 1.0f);
            viewport = glm::vec2(1, target_aspect);
        }
        //std::cout << viewport.x << ", "<< viewport.y << std::endl;
        standard_shader->set_uniform_mat4("projection", projection);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, camera_position);
        standard_shader->set_uniform_mat4("view", view);
    
        glm::vec2 position = glm::vec2(0.0f, 0.0f);

        glm::mat4 model = glm::mat4(1.0f);
        glm::vec2 size = viewport;
        model = glm::translate(model, glm::vec3(position, 0.0f));  
        model = glm::scale(model, glm::vec3(size, 1.0f)); 
        standard_shader->set_uniform_mat4("model", model);
    
        quad_mesh->draw();

        pacman_texture->bind();
        standard_shader->bind();

        standard_shader->set_uniform_mat4("projection", projection);
        standard_shader->set_uniform_mat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(glm::vec2(0.0f, 0.0f), 0.0f));
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
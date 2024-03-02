#define GL_SILENCE_DEPRECATION

#include "src/include/gl_renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <iostream>

const unsigned int PIXEL_SCALING = 3;
const unsigned int PIXEL_WIDTH = 224;
const unsigned int PIXEL_HEIGHT = 288;

const unsigned int GRID_WIDTH = 28;
const unsigned int GRID_HEIGHT = 36;
const unsigned int GRID_TILE = 8 * PIXEL_SCALING;

const unsigned int TARGET_VIEWPORT_WIDTH = PIXEL_WIDTH * PIXEL_SCALING;
const unsigned int TARGET_VIEWPORT_HEIGHT = PIXEL_HEIGHT * PIXEL_SCALING;

const char *vertex_shader_src = "#version 330 core\n"
    "layout (location = 0) in vec2 a_pos;\n"
    "layout (location = 1) in vec2 a_tex;\n"
    "out vec2 v_tex;\n"
    "uniform mat4 u_model;\n"
    "uniform mat4 u_view;\n"
    "uniform mat4 u_projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = u_projection * u_view * u_model * vec4(a_pos.xy, 0.0f, 1.0f);\n"
    "   v_tex = a_tex;\n"
    "}\0";
const char *fragment_shader_src = "#version 330 core\n"
    "out vec4 o_color;\n"
    "in vec2 v_tex;\n"
    "uniform sampler2D u_texture;\n"
    "void main()\n"
    "{\n"
    "   o_color = texture(u_texture, v_tex);\n"
    "}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float viewport_width = TARGET_VIEWPORT_WIDTH;
float viewport_height = TARGET_VIEWPORT_HEIGHT;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f);

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

    window = glfwCreateWindow(TARGET_VIEWPORT_WIDTH, TARGET_VIEWPORT_HEIGHT, "Pacman", NULL, NULL);
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

    auto tile_texture = renderer.create_texture();
    tile_texture->set_info();

    std::filesystem::path current_path = std::filesystem::current_path();
    current_path.append("../data/sprite.png");

    load_texture(current_path.string().c_str(), true, tile_texture);

    while(glfwWindowShouldClose(window) == false)
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        tile_texture->bind();
        standard_shader->bind();

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::ortho(-viewport_width * 0.5f, viewport_width * 0.5f, -viewport_height * 0.5f, viewport_height * 0.5f, -1.0f, 1.0f);
        standard_shader->set_uniform_mat4("u_projection", projection);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, camera_position);
        standard_shader->set_uniform_mat4("u_view", view);

        glm::vec2 grid_offset = glm::vec2((TARGET_VIEWPORT_WIDTH - GRID_TILE) * 0.5f, (TARGET_VIEWPORT_HEIGHT - GRID_TILE) * 0.5f);
        glm::vec2 size = glm::vec2(7 * PIXEL_SCALING, 7 * PIXEL_SCALING);
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            for (int x = 0; x < GRID_WIDTH; x++)
            {
                glm::vec2 position = glm::vec2(x * GRID_TILE - grid_offset.x, y * GRID_TILE - grid_offset.y);
 
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(position, 0.0f));  
                model = glm::scale(model, glm::vec3(size, 1.0f)); 
                standard_shader->set_uniform_mat4("u_model", model);

                quad_mesh->draw();
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    viewport_width = static_cast<float>(width);
    viewport_height = static_cast<float>(height);

    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(200.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_position += cameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_position -= cameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_position -= cameraSpeed * glm::vec3(-1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_position += cameraSpeed * glm::vec3(-1.0f, 0.0f, 0.0f);
}
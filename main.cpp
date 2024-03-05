#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
#endif

#include "src/include/sprite_asset.h"
#include "src/include/gl_renderer.h"

#include <filesystem>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//CONST
const unsigned int PIXEL_SCALING = 3;
const unsigned int PIXEL_WIDTH = 224;
const unsigned int PIXEL_HEIGHT = 288;

const unsigned int GRID_WIDTH = 28;
const unsigned int GRID_HEIGHT = 36;
const unsigned int GRID_TILE = 8 * PIXEL_SCALING;

const unsigned int TARGET_VIEWPORT_WIDTH = PIXEL_WIDTH * PIXEL_SCALING;
const unsigned int TARGET_VIEWPORT_HEIGHT = PIXEL_HEIGHT * PIXEL_SCALING;

//GLOBAL
float viewport_width = TARGET_VIEWPORT_WIDTH;
float viewport_height = TARGET_VIEWPORT_HEIGHT;

float deltaTime = 0.0f, lastFrame = 0.0f;

glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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
    auto standard_shader = renderer.create_shader(STANDARD_VERT_SOURCE, STANDARD_FRAG_SOURCE);

    std::filesystem::path maze_tilesheet_path = std::filesystem::current_path().append("../data/grid_spritesheet.png");
    auto tilesheet_texture = renderer.create_texture(maze_tilesheet_path.c_str());

    mesh_asset quad_mesh_asset = mesh_asset::get_primitive_quad();
    auto quad_mesh = renderer.create_mesh(QUAD_VERTICES, QUAD_VERTICES_LENGTH, QUAD_INDICES, QUAD_INDICES_LENGTH);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while(glfwWindowShouldClose(window) == false)
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        standard_shader->use();

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::ortho(-viewport_width * 0.5f, viewport_width * 0.5f, -viewport_height * 0.5f, viewport_height * 0.5f, -1.0f, 1.0f);
        standard_shader->set_uniform_mat4("u_projection", projection);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, camera_position);
        standard_shader->set_uniform_mat4("u_view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(GRID_TILE, GRID_TILE, 0.0f));
        standard_shader->set_uniform_mat4("u_model", model);

        quad_mesh->draw();

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
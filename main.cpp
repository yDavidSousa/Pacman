#define GL_SILENCE_DEPRECATION

#include "src/include/sprite_asset.h"
#include "src/include/gl_renderer.h"

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

const char* std_vert_source = "#version 330 core\n"
    "layout (location = 0) in vec2 a_vert;\n"
    "layout (location = 1) in vec2 a_tex;\n"
    "layout (location = 2) in mat4 a_model;\n"
    "out vec2 v_tex;\n"
    "uniform mat4 u_view;\n"
    "uniform mat4 u_projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = u_projection * u_view * a_model * vec4(a_vert.xy, 0.0f, 1.0f);\n"
    "   v_tex = a_tex;\n"
    "}\0";
const char* std_frag_source = "#version 330 core\n"
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
    auto standard_shader = renderer.create_shader(std_vert_source, std_frag_source);
    std::filesystem::path texture_path = std::filesystem::current_path().append("../data/grid_spritesheet.png");
    auto tilesheet_texture = renderer.create_texture(texture_path.c_str());

    sprite_asset tilesheet(tilesheet_texture);
    std::vector<sprite_asset> tiles = tilesheet.slice_count(16, 9, {1, 1}, {0, 0});

    sprite_asset tile = tiles[0];
    std::vector<float> tex_coord = 
    {
        (tile.x + tile.w) / tilesheet.w, (tile.y + tile.h) / tilesheet.h,
        (tile.x + tile.w) / tilesheet.w, tile.y / tilesheet.h,
        tile.x / tilesheet.w, tile.y / tilesheet.h,
        tile.x / tilesheet.w, (tile.y + tile.h) / tilesheet.h
    };

    std::cout << "Min: {" << tile.x / tilesheet.w << ", " << tile.y / tilesheet.h  << "}" << std::endl;
    std::cout << "Max: {" << (tile.x + tile.w) / tilesheet.w << ", " << (tile.y + tile.h) / tilesheet.h << "}" << std::endl;

    mesh_data mesh(quad_vertices, quad_indices, tex_coord);
    auto quad_mesh = renderer.create_mesh(mesh);

    while(glfwWindowShouldClose(window) == false)
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        tilesheet_texture->bind();
        standard_shader->use();

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::ortho(-viewport_width * 0.5f, viewport_width * 0.5f, -viewport_height * 0.5f, viewport_height * 0.5f, -1.0f, 1.0f);
        standard_shader->set_uniform_mat4("u_projection", projection);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, camera_position);
        standard_shader->set_uniform_mat4("u_view", view);

        std::vector<glm::mat4> models;
        std::vector<float*> tex_coords;
        glm::vec2 grid_offset = glm::vec2((TARGET_VIEWPORT_WIDTH - GRID_TILE) * 0.5f, (TARGET_VIEWPORT_HEIGHT - GRID_TILE) * 0.5f);
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            for (int x = 0; x < GRID_WIDTH; x++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                glm::vec2 position = glm::vec2(x * GRID_TILE - grid_offset.x, y * GRID_TILE - grid_offset.y);
                model = glm::translate(model, glm::vec3(position, 0.0f));  
                model = glm::scale(model, glm::vec3(glm::vec2(GRID_TILE, GRID_TILE), 1.0f)); 
                models.push_back(model);
            }
        }
        quad_mesh->draw(models);

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
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

const int maze_data[] = {
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
33,43,43,43,43,43,43,43,43,43,43,43,43,11,10,43,43,43,43,43,43,43,43,43,43,43,43,32,
35,12,12,12,12,12,12,12,12,12,12,12,12,25,24,12,12,12,12,12,12,12,12,12,12,12,12,34,
35,12,23,47,47,22,12,23,47,47,47,22,12,25,24,12,23,47,47,47,22,12,23,47,47,22,12,34,
35,12,25,12,12,24,12,25,12,12,12,24,12,25,24,12,25,12,12,12,24,12,25,12,12,24,12,34,
35,12,27,20,20,26,12,27,20,20,20,26,12,27,26,12,27,20,20,20,26,12,27,20,20,26,12,34,
35,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,34,
35,12,23,47,47,22,12,23,22,12,23,47,47,47,47,47,47,22,12,23,22,12,23,47,47,22,12,34,
35,12,27,20,20,26,12,25,24,12,27,20,20,03,02,20,20,26,12,25,24,12,27,20,20,26,12,34,
35,12,12,12,12,12,12,25,24,12,12,12,12,25,24,12,12,12,12,25,24,12,12,12,12,12,12,34,
37,44,44,44,44,22,12,25,04,47,47,22,12,25,24,12,23,47,47,05,24,12,23,44,44,44,44,36,
12,12,12,12,12,35,12,25,02,20,20,26,12,27,26,12,27,20,20,03,24,12,34,12,12,12,12,12,
12,12,12,12,12,35,12,25,24,12,12,12,12,12,12,12,12,12,12,25,24,12,34,12,12,12,12,12,
12,12,12,12,12,35,12,25,24,12,29,44,01,12,12,00,44,28,12,25,24,12,34,12,12,12,12,12,
43,43,43,43,43,26,12,27,26,12,34,12,12,12,12,12,12,35,12,27,26,12,27,43,43,43,43,43,
12,12,12,12,12,12,12,12,12,12,34,12,12,12,12,12,12,35,12,12,12,12,12,12,12,12,12,12,
44,44,44,44,44,22,12,23,22,12,34,12,12,12,12,12,12,35,12,23,22,12,23,44,44,44,44,44,
12,12,12,12,12,35,12,25,24,12,31,42,42,42,42,42,42,30,12,25,24,12,34,12,12,12,12,12,
12,12,12,12,12,35,12,25,24,12,12,12,12,12,12,12,12,12,12,25,24,12,34,12,12,12,12,12,
12,12,12,12,12,35,12,25,24,12,23,47,47,47,47,47,47,22,12,25,24,12,34,12,12,12,12,12,
33,43,43,43,43,26,12,27,26,12,27,20,20,03,02,20,20,26,12,27,26,12,27,43,43,43,43,32,
35,12,12,12,12,12,12,12,12,12,12,12,12,25,24,12,12,12,12,12,12,12,12,12,12,12,12,34,
35,12,23,47,47,22,12,23,47,47,47,22,12,25,24,12,23,47,47,47,22,12,23,47,47,22,12,34,
35,12,27,20,03,24,12,27,20,20,20,26,12,27,26,12,27,20,20,20,26,12,25,02,20,26,12,34,
35,12,12,12,25,24,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,25,24,12,12,12,34,
39,47,22,12,25,24,12,23,22,12,23,47,47,47,47,47,47,22,12,23,22,12,25,24,12,23,47,38,
41,20,26,12,27,26,12,25,24,12,27,20,20,03,02,20,20,26,12,25,24,12,27,26,12,27,20,40,
35,12,12,12,12,12,12,25,24,12,12,12,12,25,24,12,12,12,12,25,24,12,12,12,12,12,12,34,
35,12,23,47,47,47,47,05,04,47,47,22,12,25,24,12,23,47,47,05,04,47,47,47,47,22,12,34,
35,12,27,20,20,20,20,20,20,20,20,26,12,27,26,12,27,20,20,20,20,20,20,20,20,26,12,34,
35,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,34,
37,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,36,
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
};

//const int small_dots;
//const int flashing_dots;

//GLOBAL
float viewport_width = TARGET_VIEWPORT_WIDTH;
float viewport_height = TARGET_VIEWPORT_HEIGHT;

float deltaTime = 0.0f, lastFrame = 0.0f;

glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

int main(int argc, char** argv)
{
	GLFWwindow* window;

	if (glfwInit() == false)
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
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	gl_renderer renderer;
	auto standard_shader = renderer.create_shader(STANDARD_VERT_SOURCE, STANDARD_FRAG_SOURCE);

	std::filesystem::path maze_tilesheet_path = std::filesystem::current_path().append("../data/grid_spritesheet.png");
	auto tilesheet_texture = renderer.create_texture(maze_tilesheet_path.string().c_str());
	sprite_asset tilesheet_sprite = sprite_asset(0.0f, 0.0f, tilesheet_texture->get_width(), tilesheet_texture->get_height());
	std::vector<sprite_asset> tiles = sprite_slice_count(tilesheet_sprite, 16, 9, { 1, 1 }, { 1, 1 });

	float grid_offset_x = TARGET_VIEWPORT_WIDTH / 2.0f;
	float grid_offset_y = TARGET_VIEWPORT_HEIGHT / 2.0f;

	int tiles_count = sizeof(maze_data) / sizeof(float);
	std::vector<float> grid_vertices;
	for (int i = 0; i < tiles_count; i++)
	{
		if(maze_data[i] == 12) continue;
		int x = i % GRID_WIDTH;
		int y = i / GRID_WIDTH;

		grid_vertices.push_back(x * GRID_TILE - grid_offset_x);
		grid_vertices.push_back(y * GRID_TILE * -1.0f + grid_offset_y);

		grid_vertices.push_back(x * GRID_TILE + GRID_TILE - grid_offset_x);
		grid_vertices.push_back(y * GRID_TILE * -1.0f + grid_offset_y);

		grid_vertices.push_back(x * GRID_TILE + GRID_TILE - grid_offset_x);
		grid_vertices.push_back(y * GRID_TILE * -1.0f - GRID_TILE + grid_offset_y);

		grid_vertices.push_back(x * GRID_TILE - grid_offset_x);
		grid_vertices.push_back(y * GRID_TILE * -1.0f - GRID_TILE + grid_offset_y);
	}
	
	std::vector<unsigned int> grid_indices;
	int index = 0;
	for (int i = 0; i < tiles_count; i++)
	{
		if(maze_data[i] == 12) continue;

		grid_indices.push_back(index * 4);
		grid_indices.push_back(index * 4 + 1);
		grid_indices.push_back(index * 4 + 2);

		grid_indices.push_back(index * 4);
		grid_indices.push_back(index * 4 + 3);
		grid_indices.push_back(index * 4 + 2);
		index++;
	}

	std::vector<float> grid_text_coords;
	for (int i = 0; i < tiles_count; i++)
	{
		if(maze_data[i] == 12) continue;

		sprite_asset tile = tiles[maze_data[i] + 48];
		grid_text_coords.push_back((tile.x) / tilesheet_sprite.w);
		grid_text_coords.push_back((tile.y) / tilesheet_sprite.h);

		grid_text_coords.push_back((tile.x + tile.w) / tilesheet_sprite.w);
		grid_text_coords.push_back((tile.y) / tilesheet_sprite.h);

		grid_text_coords.push_back((tile.x + tile.w) / tilesheet_sprite.w);
		grid_text_coords.push_back((tile.y + tile.h) / tilesheet_sprite.h);

		grid_text_coords.push_back((tile.x) / tilesheet_sprite.w);
		grid_text_coords.push_back((tile.y + tile.h) / tilesheet_sprite.h);
	}

	std::cout << "Vertices: " << grid_vertices.size() / 2.0f << std::endl;
	std::cout << "Triangles: " << grid_indices.size() / 3.0f << std::endl;
	std::cout << "UVs: " << grid_text_coords.size() / 2.0f << std::endl;
	auto grid_mesh = renderer.create_mesh(grid_vertices.data(), grid_vertices.size(), grid_indices.data(), grid_indices.size(), grid_text_coords.data(), grid_text_coords.size());

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (glfwWindowShouldClose(window) == false)
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		process_input(window);

		glClear(GL_COLOR_BUFFER_BIT);

		tilesheet_texture->bind();
		standard_shader->use();

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::ortho(-viewport_width * 0.5f, viewport_width * 0.5f, -viewport_height * 0.5f, viewport_height * 0.5f, -1.0f, 1.0f);
		standard_shader->set_uniform_mat4("u_projection", projection);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, camera_position);
		standard_shader->set_uniform_mat4("u_view", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		standard_shader->set_uniform_mat4("u_model", model);

		grid_mesh->draw();

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

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = static_cast<float>(212.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera_position += cameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_position -= cameraSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_position -= cameraSpeed * glm::vec3(-1.0f, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_position += cameraSpeed * glm::vec3(-1.0f, 0.0f, 0.0f);
}
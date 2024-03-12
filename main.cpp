#include <iostream>
#include <vector>
#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/imgui/imgui_impl_glfw.h"
#include "src/imgui/imgui_impl_opengl3.h"

#include "src/include/sprite_asset.h"
#include "src/include/gl_renderer.h"

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
const int dots_data[] = {
	113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 127, 128, 129, 130, 131, 132,
	133, 134, 135, 136, 137, 138, 141, 146, 152, 155, 161, 166, 174, 180, 183, 189, 197, 202,
	208, 211, 217, 222, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 234, 235, 236, 237,
	238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 253, 258, 261, 270, 273,
	278, 281, 286, 289, 298, 301, 306, 309, 310, 311, 312, 313, 314, 317, 318, 319, 320, 323,
	324, 325, 326, 329, 330, 331, 332, 333, 334, 342, 357, 370, 385, 398, 413, 426, 441, 454,
	469, 482, 497, 510, 525, 538, 553, 566, 581, 594, 609, 622, 637, 645, 646, 647, 648, 649,
	650, 651, 652, 653, 654, 655, 656, 659, 660, 661, 662, 663, 664, 665, 666, 667, 668, 669,
	670, 673, 678, 684, 687, 693, 698, 701, 706, 712, 715, 721, 726, 730, 731, 734, 735, 736,
	737, 738, 739, 740, 743, 744, 745, 746, 747, 748, 749, 752, 753, 759, 762, 765, 774, 777,
	780, 787, 790, 793, 802, 805, 808, 813, 814, 815, 816, 817, 818, 821, 822, 823, 824, 827,
	828, 829, 830, 833, 834, 835, 836, 837, 838, 841, 852, 855, 866, 869, 880, 883, 894, 897,
	898, 899, 900, 901, 902, 903, 904, 905, 906, 907, 908, 909, 910, 911, 912, 913, 914, 915,
	916, 917, 918, 919, 920, 921, 922
};
const int energizers_data[] = { 169, 194, 729, 754 };

struct actor
{
    glm::vec2 position;
    glm::vec2 scale;
    glm::vec2 direction;
    float speed;
    sprite_asset* sprite;
};

//GLOBAL
float viewport_width = TARGET_VIEWPORT_WIDTH;
float viewport_height = TARGET_VIEWPORT_HEIGHT;

float deltaTime = 0.0f, lastFrame = 0.0f;

glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

int main(int argc, char** argv)
{
    auto current_path = std::filesystem::current_path();
    auto base_path = std::filesystem::path(argv[0]).remove_filename();

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

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

	gl_renderer renderer;
	std::vector<gl_mesh*> dots_meshes;
	std::vector<gl_mesh*> energizers_meshes;
    bool* maze_collision = new bool[GRID_WIDTH * GRID_HEIGHT];

	auto standard_shader = renderer.create_shader(STANDARD_VERT_SOURCE, STANDARD_FRAG_SOURCE);

	auto tilesheet_texture = renderer.create_texture("/Users/davidsousa/Documents/Projects/pacman/data/tilesheet.png");
	std::vector<sprite_asset> tiles = sprite_slice_count(tilesheet_texture.get(), 16, 9, { 1, 1 }, { 1, 1 });

    auto spritesheet_texture = renderer.create_texture("/Users/davidsousa/Documents/Projects/pacman/data/spritesheet.png");
    std::vector<sprite_asset> sprites = sprite_slice_count(spritesheet_texture.get(), 14, 14, { 0, 0 }, { 0, 0 });

	// MAZE STATIC
	float grid_offset_x = TARGET_VIEWPORT_WIDTH / 2.0f;
	float grid_offset_y = TARGET_VIEWPORT_HEIGHT / 2.0f;

	int tiles_count = sizeof(maze_data) / sizeof(float);
	std::vector<float> maze_vertices;
	for (int i = 0; i < tiles_count; i++)
	{
        maze_collision[i] = false;
		if(maze_data[i] == 12) continue;

        maze_collision[i] = true;
		int x = i % GRID_WIDTH;
		int y = i / GRID_WIDTH;

		maze_vertices.push_back(x * GRID_TILE - grid_offset_x);
		maze_vertices.push_back(y * GRID_TILE * -1.0f - GRID_TILE + grid_offset_y);

		maze_vertices.push_back(x * GRID_TILE + GRID_TILE - grid_offset_x);
		maze_vertices.push_back(y * GRID_TILE * -1.0f - GRID_TILE + grid_offset_y);

		maze_vertices.push_back(x * GRID_TILE + GRID_TILE - grid_offset_x);
		maze_vertices.push_back(y * GRID_TILE * -1.0f + grid_offset_y);

		maze_vertices.push_back(x * GRID_TILE - grid_offset_x);
		maze_vertices.push_back(y * GRID_TILE * -1.0f + grid_offset_y);
	}
	
	std::vector<unsigned int> maze_indices;
	int index = 0;
	for (int i = 0; i < tiles_count; i++)
	{
		if(maze_data[i] == 12) continue;

		maze_indices.push_back(index * 4);
		maze_indices.push_back(index * 4 + 1);
		maze_indices.push_back(index * 4 + 2);

		maze_indices.push_back(index * 4);
		maze_indices.push_back(index * 4 + 3);
		maze_indices.push_back(index * 4 + 2);
		index++;
	}

	std::vector<float> maze_tex_coords;
	for (int i = 0; i < tiles_count; i++)
	{
		if(maze_data[i] == 12) continue;

		sprite_asset tile = tiles[maze_data[i] + 48];
        for (int j = 0; j < QUAD_TEX_COORDS_LENGTH; ++j)
        {
            maze_tex_coords.push_back(tile.tex_coords[j]);
        }
	}
	auto maze_mesh = renderer.create_mesh(maze_vertices.data(), maze_vertices.size(), maze_indices.data(), maze_indices.size(), maze_tex_coords.data(), maze_tex_coords.size());

	// DOTS STATIC
    std::vector<actor> dots;
	int dots_count = sizeof(dots_data) / sizeof(int);
	for (int i = 0; i < dots_count; i++)
	{
		int x = dots_data[i] % GRID_WIDTH;
		int y = dots_data[i] / GRID_WIDTH;

        dots.push_back({
            .position = {x * GRID_TILE + GRID_TILE * 0.5f - grid_offset_x, y * GRID_TILE * -1.0f - GRID_TILE * 0.5f + grid_offset_y},
            .scale = {GRID_TILE, GRID_TILE},
            .sprite = &tiles[13 + 48]
        });
	}

	// ENERGIZERS STATIC
    std::vector<actor> energizers;
    int energizers_count = sizeof(energizers_data) / sizeof(int);
	for (int i = 0; i < energizers_count; i++)
	{
		int x = energizers_data[i] % GRID_WIDTH;
		int y = energizers_data[i] / GRID_WIDTH;

        energizers.push_back({
            .position = {x * GRID_TILE + GRID_TILE * 0.5f - grid_offset_x, y * GRID_TILE * -1.0f - GRID_TILE * 0.5f + grid_offset_y},
            .scale = {GRID_TILE, GRID_TILE},
            .sprite = &tiles[15 + 48]
        });
	}

    actor player = {};
    player.position = glm::vec2(0.0f, -204.0f);
    player.scale = glm::vec2(16.0f * PIXEL_SCALING, 16.0f * PIXEL_SCALING);
    player.direction = glm::vec2(1.0f, 0.0f);
    player.speed = 16.0f * PIXEL_SCALING;
    player.sprite = &tiles[15 + 48];

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (glfwWindowShouldClose(window) == false)
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		process_input(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		standard_shader->use();

		auto projection = glm::mat4(1.0f);
		projection = glm::ortho(-viewport_width * 0.5f, viewport_width * 0.5f, -viewport_height * 0.5f, viewport_height * 0.5f, -1.0f, 1.0f);
		standard_shader->set_uniform_mat4("u_projection", projection);

		auto view = glm::mat4(1.0f);
		view = glm::translate(view, camera_position);
		standard_shader->set_uniform_mat4("u_view", view);

		auto model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		standard_shader->set_uniform_mat4("u_model", model);

        tilesheet_texture->bind();
		maze_mesh->draw();

		for (int i = 0; i < dots.size(); i++)
		{
            renderer.push_quad(dots[i].position, dots[i].scale, dots[i].sprite->tex_coords);
		}
		for (int i = 0; i < energizers.size(); i++)
		{
            renderer.push_quad(energizers[i].position, energizers[i].scale, energizers[i].sprite->tex_coords);
		}
        renderer.push_quad(player.position, player.scale, player.sprite->tex_coords);
        renderer.draw();

        player.position += player.direction * player.speed * deltaTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
		glfwPollEvents();
	}

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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
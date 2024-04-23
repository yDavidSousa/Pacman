#if BESKAR_EDITOR
#include "../beskar/src/editor/imgui/imgui.h"
#endif
#include <beskar_engine/application.h>
#include <beskar_engine/mesh.h>

const unsigned int PIXEL_SCALING = 3;
const unsigned int PIXEL_WIDTH = 224;
const unsigned int PIXEL_HEIGHT = 288;

const unsigned int GRID_WIDTH = 28;
const unsigned int GRID_HEIGHT = 36;
const unsigned int GRID_TILE = 8 * PIXEL_SCALING;

const unsigned int TARGET_VIEWPORT_WIDTH = PIXEL_WIDTH * PIXEL_SCALING;
const unsigned int TARGET_VIEWPORT_HEIGHT = PIXEL_HEIGHT * PIXEL_SCALING;

const int maze_data[] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 33, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43,
                         43, 11, 10, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 32, 35, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 12, 12, 25, 24, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 34, 35, 12, 23, 47,
                         47, 22, 12, 23, 47, 47, 47, 22, 12, 25, 24, 12, 23, 47, 47, 47, 22, 12, 23, 47, 47, 22, 12, 34,
                         35, 12, 25, 12, 12, 24, 12, 25, 12, 12, 12, 24, 12, 25, 24, 12, 25, 12, 12, 12, 24, 12, 25, 12,
                         12, 24, 12, 34, 35, 12, 27, 20, 20, 26, 12, 27, 20, 20, 20, 26, 12, 27, 26, 12, 27, 20, 20, 20,
                         26, 12, 27, 20, 20, 26, 12, 34, 35, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 34, 35, 12, 23, 47, 47, 22, 12, 23, 22, 12, 23, 47,
                         47, 47, 47, 47, 47, 22, 12, 23, 22, 12, 23, 47, 47, 22, 12, 34, 35, 12, 27, 20, 20, 26, 12, 25,
                         24, 12, 27, 20, 20, 03, 02, 20, 20, 26, 12, 25, 24, 12, 27, 20, 20, 26, 12, 34, 35, 12, 12, 12,
                         12, 12, 12, 25, 24, 12, 12, 12, 12, 25, 24, 12, 12, 12, 12, 25, 24, 12, 12, 12, 12, 12, 12, 34,
                         37, 44, 44, 44, 44, 22, 12, 25, 04, 47, 47, 22, 12, 25, 24, 12, 23, 47, 47, 05, 24, 12, 23, 44,
                         44, 44, 44, 36, 12, 12, 12, 12, 12, 35, 12, 25, 02, 20, 20, 26, 12, 27, 26, 12, 27, 20, 20, 03,
                         24, 12, 34, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 35, 12, 25, 24, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 25, 24, 12, 34, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 35, 12, 25, 24, 12, 29, 44,
                         01, 12, 12, 00, 44, 28, 12, 25, 24, 12, 34, 12, 12, 12, 12, 12, 43, 43, 43, 43, 43, 26, 12, 27,
                         26, 12, 34, 12, 12, 12, 12, 12, 12, 35, 12, 27, 26, 12, 27, 43, 43, 43, 43, 43, 12, 12, 12, 12,
                         12, 12, 12, 12, 12, 12, 34, 12, 12, 12, 12, 12, 12, 35, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                         44, 44, 44, 44, 44, 22, 12, 23, 22, 12, 34, 12, 12, 12, 12, 12, 12, 35, 12, 23, 22, 12, 23, 44,
                         44, 44, 44, 44, 12, 12, 12, 12, 12, 35, 12, 25, 24, 12, 31, 42, 42, 42, 42, 42, 42, 30, 12, 25,
                         24, 12, 34, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 35, 12, 25, 24, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 25, 24, 12, 34, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 35, 12, 25, 24, 12, 23, 47,
                         47, 47, 47, 47, 47, 22, 12, 25, 24, 12, 34, 12, 12, 12, 12, 12, 33, 43, 43, 43, 43, 26, 12, 27,
                         26, 12, 27, 20, 20, 03, 02, 20, 20, 26, 12, 27, 26, 12, 27, 43, 43, 43, 43, 32, 35, 12, 12, 12,
                         12, 12, 12, 12, 12, 12, 12, 12, 12, 25, 24, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 34,
                         35, 12, 23, 47, 47, 22, 12, 23, 47, 47, 47, 22, 12, 25, 24, 12, 23, 47, 47, 47, 22, 12, 23, 47,
                         47, 22, 12, 34, 35, 12, 27, 20, 03, 24, 12, 27, 20, 20, 20, 26, 12, 27, 26, 12, 27, 20, 20, 20,
                         26, 12, 25, 02, 20, 26, 12, 34, 35, 12, 12, 12, 25, 24, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 12, 12, 12, 25, 24, 12, 12, 12, 34, 39, 47, 22, 12, 25, 24, 12, 23, 22, 12, 23, 47,
                         47, 47, 47, 47, 47, 22, 12, 23, 22, 12, 25, 24, 12, 23, 47, 38, 41, 20, 26, 12, 27, 26, 12, 25,
                         24, 12, 27, 20, 20, 03, 02, 20, 20, 26, 12, 25, 24, 12, 27, 26, 12, 27, 20, 40, 35, 12, 12, 12,
                         12, 12, 12, 25, 24, 12, 12, 12, 12, 25, 24, 12, 12, 12, 12, 25, 24, 12, 12, 12, 12, 12, 12, 34,
                         35, 12, 23, 47, 47, 47, 47, 05, 04, 47, 47, 22, 12, 25, 24, 12, 23, 47, 47, 05, 04, 47, 47, 47,
                         47, 22, 12, 34, 35, 12, 27, 20, 20, 20, 20, 20, 20, 20, 20, 26, 12, 27, 26, 12, 27, 20, 20, 20,
                         20, 20, 20, 20, 20, 26, 12, 34, 35, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 34, 37, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44,
                         44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 36, 12, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                         12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
                         12,};
const int dots_data[] = {113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 127, 128, 129, 130, 131, 132, 133,
                         134, 135, 136, 137, 138, 141, 146, 152, 155, 161, 166, 174, 180, 183, 189, 197, 202, 208, 211,
                         217, 222, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 234, 235, 236, 237, 238, 239, 240,
                         241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 253, 258, 261, 270, 273, 278, 281, 286, 289,
                         298, 301, 306, 309, 310, 311, 312, 313, 314, 317, 318, 319, 320, 323, 324, 325, 326, 329, 330,
                         331, 332, 333, 334, 342, 357, 370, 385, 398, 413, 426, 441, 454, 469, 482, 497, 510, 525, 538,
                         553, 566, 581, 594, 609, 622, 637, 645, 646, 647, 648, 649, 650, 651, 652, 653, 654, 655, 656,
                         659, 660, 661, 662, 663, 664, 665, 666, 667, 668, 669, 670, 673, 678, 684, 687, 693, 698, 701,
                         706, 712, 715, 721, 726, 730, 731, 734, 735, 736, 737, 738, 739, 740, 743, 744, 745, 746, 747,
                         748, 749, 752, 753, 759, 762, 765, 774, 777, 780, 787, 790, 793, 802, 805, 808, 813, 814, 815,
                         816, 817, 818, 821, 822, 823, 824, 827, 828, 829, 830, 833, 834, 835, 836, 837, 838, 841, 852,
                         855, 866, 869, 880, 883, 894, 897, 898, 899, 900, 901, 902, 903, 904, 905, 906, 907, 908, 909,
                         910, 911, 912, 913, 914, 915, 916, 917, 918, 919, 920, 921, 922};
const int energizers_data[] = {169, 194, 729, 754};

struct actor
{
    glm::vec2 position;
    glm::vec2 scale;
    glm::vec2 direction;
    float speed;
};

unsigned int tilesheet_texture;
unsigned int standard_shader;

actor player = {};
mesh* maze_mesh;

void application::initialize()
{
    tilesheet_texture = resource_system->load_texture("textures/tilesheet.png");
    standard_shader = resource_system->load_shader("shaders/standard.glsl");

    // MAZE STATIC
    float grid_offset_x = TARGET_VIEWPORT_WIDTH / 2.0f;
    float grid_offset_y = TARGET_VIEWPORT_HEIGHT / 2.0f;

    int tiles_count = sizeof(maze_data) / sizeof(float);
    std::vector<float> maze_vertices;
    for (int i = 0; i < tiles_count; i++)
    {
        if (maze_data[i] == 12) continue;

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
        if (maze_data[i] == 12) continue;

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
        if (maze_data[i] == 12) continue;

        sprite_metadata tile = resource_system->lookup_sprite("textures/tilesheet.png", maze_data[i] + 48);
        texture* texture_ptr = resource_system->lookup_texture(tilesheet_texture);

        int texture_width = texture_ptr->get_width();
        int texture_height = texture_ptr->get_height();
        float left = tile.x / texture_width;
        float right = (tile.x + tile.w) / texture_width;
        float bottom = tile.y / texture_height;
        float top = (tile.y + tile.h) / texture_height;
        float* tex_coords = new float[]{
                left, bottom,
                right, bottom,
                right, top,
                left, top
        };

        for (int j = 0; j < QUAD_TEX_COORDS_LENGTH; ++j)
        {
            maze_tex_coords.push_back(tex_coords[j]);
        }
    }
    maze_mesh = new mesh(maze_vertices.data(), maze_vertices.size(), maze_indices.data(), maze_indices.size(), maze_tex_coords.data(), maze_tex_coords.size());
}

void application::update(float delta_time)
{
    shader* standard_shader_ptr = resource_system->lookup_shader(standard_shader);
    standard_shader_ptr->use();

    float white_color[4] = {1, 1, 1, 1};
    standard_shader_ptr->set_uniform_4fv("u_color", white_color);

    auto projection = glm::mat4(1.0f);
    float viewport_width = static_cast<float>(TARGET_VIEWPORT_WIDTH);
    float viewport_height = static_cast<float>(TARGET_VIEWPORT_HEIGHT);
    projection = glm::ortho(-viewport_width * 0.5f, viewport_width * 0.5f, -viewport_height * 0.5f, viewport_height * 0.5f, -1.0f, 1.0f);
    standard_shader_ptr->set_uniform_mat4("u_projection", projection);

    auto view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    standard_shader_ptr->set_uniform_mat4("u_view", view);

    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    standard_shader_ptr->set_uniform_mat4("u_model", model);

    texture* tilesheet_texture_ptr = resource_system->lookup_texture(tilesheet_texture);
    tilesheet_texture_ptr->bind();

    maze_mesh->draw();
    renderer_system->draw();
}

void application::gui()
{
#if BESKAR_EDITOR
    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("Window"))
        {
            ImGui::MenuItem("Game Debug");
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
#endif
}

application* beskar_main(int argc, char **argv)
{
    return new application(argv[0], TARGET_VIEWPORT_WIDTH, TARGET_VIEWPORT_HEIGHT);
}
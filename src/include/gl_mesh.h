#ifndef PACMAN_GL_MESH_H
#define PACMAN_GL_MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const std::vector<float> quad_vertices = {
     0.5f,  0.5f, // top right
     0.5f, -0.5f, // bottom right
    -0.5f, -0.5f, // bottom left
    -0.5f,  0.5f  // top left 
};

const std::vector<unsigned int> quad_indices = {
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

const std::vector<float> quad_text_coords = {
    1.0f, 1.0f, // top right
    1.0f, 0.0f, // bottom right
    0.0f, 0.0f, // bottom left
    0.0f, 1.0f  // top left 
};

struct mesh_data
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> tex_coords;

    mesh_data();
    mesh_data(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> tex_coords);

    static const mesh_data get_primitive_quad();
};

class gl_mesh
{
    public:
        gl_mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> tex_coords);
        ~gl_mesh();

        void draw(const std::vector<glm::mat4>& models);
    private:
        unsigned int vao, ebo, instance_bo;
        unsigned int vbo_vertices;
        unsigned int vbo_tex_coords;
        unsigned int vbo_color;
};

#endif
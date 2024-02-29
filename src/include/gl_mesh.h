#ifndef PACMAN_GL_MESH_H
#define PACMAN_GL_MESH_H

#include <vector>

const std::vector<float> quad_vertices = {
    // positions          // colors           // texture coords
     1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

const std::vector<unsigned int> quad_indices = {
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

class gl_mesh
{
    public:
        gl_mesh();
        ~gl_mesh();

        void set_vertices(std::vector<float> vertices);
        void set_indices(std::vector<unsigned int> indices);
        void bind();
        void draw();

    private:
        unsigned int va_id, vb_id, eb_id;
        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;
};

#endif
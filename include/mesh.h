#ifndef PACMAN_MESH_H
#define PACMAN_MESH_H

class mesh
{
    public:
        mesh(const float *vertices, const unsigned int *triangles);
        ~mesh();

        void bind_layout();
        void draw();
    private:
        unsigned int VBO, VAO, EBO;

        const float *m_vertices;
        const unsigned int *m_triangles;
};

#endif
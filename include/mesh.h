#ifndef PACMAN_MESH_H
#define PACMAN_MESH_H

#include <vector>

class mesh
{
    public:
        mesh(std::vector<float> vertices);
        ~mesh();

        void bind();
        void draw();

    private:
        unsigned int va_id, vb_id;
        std::vector<float> vb_data;
};

#endif
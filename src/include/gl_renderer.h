#ifndef PACMAN_GL_RENDERER_H
#define PACMAN_GL_RENDERER_H

#include "gl_shader.h"
#include "gl_mesh.h"
#include "gl_texture.h"

class gl_renderer
{
    public:
        gl_renderer();
        ~gl_renderer();

        [[nodiscard]] std::unique_ptr<gl_shader> create_shader(const char* vert_source, const char* frag_source);
        [[nodiscard]] std::unique_ptr<gl_mesh> create_mesh(const float* vertices, const unsigned long vert_length, const unsigned int* indices, const unsigned long ind_length, const float* tex_coords, const unsigned long tex_coords_length);
        [[nodiscard]] std::unique_ptr<gl_texture> create_texture(const char* path);
};

#endif
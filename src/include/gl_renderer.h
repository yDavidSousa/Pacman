#ifndef PACMAN_GL_RENDERER_H
#define PACMAN_GL_RENDERER_H

#include "gl_shader.h"
#include "gl_mesh.h"
#include "gl_texture.h"

class gl_renderer
{
    public:
        gl_renderer();
        [[nodiscard]] std::unique_ptr<gl_shader> create_shader();
        [[nodiscard]] std::unique_ptr<gl_mesh> create_mesh();
        [[nodiscard]] std::unique_ptr<gl_texture> create_texture();

        void render();
};

#endif
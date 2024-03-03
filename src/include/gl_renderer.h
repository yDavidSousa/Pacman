#ifndef PACMAN_GL_RENDERER_H
#define PACMAN_GL_RENDERER_H

#include "gl_shader.h"
#include "gl_mesh.h"
#include "gl_texture.h"

class gl_renderer
{
    public:
        gl_renderer();
        [[nodiscard]] std::unique_ptr<gl_shader> create_shader(const char* vert_source, const char* frag_source);
        [[nodiscard]] std::unique_ptr<gl_mesh> create_mesh(const mesh_data& data);
        [[nodiscard]] std::unique_ptr<gl_texture> create_texture(const char* path);

        void push_quad(const glm::vec2 position, const glm::vec2 size, const glm::vec4 color);
        void push_quad(const glm::vec2 position, const glm::vec2 size, const unsigned int texture_id);

        void render();
};

#endif
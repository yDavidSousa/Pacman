#ifndef PACMAN_GL_SHADER_H
#define PACMAN_GL_SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class gl_shader
{
    public:
        gl_shader();
        ~gl_shader();

        void create(const char *vertex_src, const char *fragment_src);
        void link();
        void bind();

        void set_uniform_mat4(const char *name, glm::mat4 mat4);
    private:
        unsigned int program_id;
        unsigned int vertex_id;
        unsigned int fragment_id;
};

#endif
#ifndef PACMAN_GL_SHADER_H
#define PACMAN_GL_SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class gl_shader
{
    public:
        gl_shader(const char* vert_source, const char* frag_source);
        ~gl_shader();

        void use();
        void set_uniform_mat4(const char *name, glm::mat4 mat4);
    private:
        unsigned int m_program;
};

#endif
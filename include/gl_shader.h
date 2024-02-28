#ifndef PACMAN_GL_SHADER_H
#define PACMAN_GL_SHADER_H

class gl_shader
{
    public:
        gl_shader();
        ~gl_shader();

        void create(const char *vertex_src, const char *fragment_src);
        void link();
        void bind();

        unsigned int program_id;
    private:
        unsigned int vertex_id;
        unsigned int fragment_id;
};

#endif
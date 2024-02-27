#ifndef PACMAN_SHADER_H
#define PACMAN_SHADER_H

class shader
{
    public:
        shader();
        ~shader();

        void create(const char *vertex_src, const char *fragment_src);
        void link();
        void bind();

        unsigned int program_id;
    private:
        unsigned int vertex_id;
        unsigned int fragment_id;
};

#endif
#ifndef PACMAN_GL_TEXTURE_H
#define PACMAN_GL_TEXTURE_H

#include <iostream>

class gl_texture
{
    public:
        gl_texture(int width, int height, unsigned char* data);
        ~gl_texture();

        void bind();
        unsigned int get_id();
    private:
        unsigned int m_id;
        int width, height;
};

#endif
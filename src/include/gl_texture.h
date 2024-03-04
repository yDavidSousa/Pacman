#ifndef PACMAN_GL_TEXTURE_H
#define PACMAN_GL_TEXTURE_H

#include <iostream>

class gl_texture
{
    public:
        gl_texture(int width, int height, int nr_channel, unsigned char* data);
        ~gl_texture();

        void bind();

        int get_width() const;
        int get_height() const;
    private:
        unsigned int m_tbo;
        int m_width, m_height;
};

#endif
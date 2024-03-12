#ifndef PACMAN_GL_TEXTURE_H
#define PACMAN_GL_TEXTURE_H

#include <iostream>

class gl_texture
{
    public:
        gl_texture(float width, float height, int channels, const unsigned char* data);
        ~gl_texture();

        void bind();

        float get_width() const { return m_width; };
        float get_height() const { return m_height; };
    private:
        unsigned int m_tbo;
        float m_width, m_height;
};

#endif
#include "include/gl_texture.h"

#include <GL/glew.h>

gl_texture::gl_texture(int width, int height, int nr_channel, unsigned char* data) : m_width(width), m_height(height)
{
    glGenTextures(1, &m_tbo); 

    // Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned int format;
    if (nr_channel == 1)
        format = GL_RED;
    else if (nr_channel == 3)
        format = GL_RGB;
    else if (nr_channel == 4)
        format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, m_tbo);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

gl_texture::~gl_texture()
{
    glDeleteTextures(1, &m_tbo);
}

int gl_texture::get_width() const { return m_width; }
int gl_texture::get_height() const { return m_height; }

void gl_texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_tbo);
}
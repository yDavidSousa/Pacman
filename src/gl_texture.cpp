#include "include/gl_texture.h"

#include <GL/glew.h>

gl_texture::gl_texture(float width, float height, int channels, const unsigned char* data) : m_width(width), m_height(height)
{
    glGenTextures(1, &m_tbo); 
    glBindTexture(GL_TEXTURE_2D, m_tbo);

    // Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned int format;
    switch(channels)
    {
        case 1:
            format = GL_RED;
            break;
        case 2:
            format = GL_RG;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

gl_texture::~gl_texture()
{
    glDeleteTextures(1, &m_tbo);
}

void gl_texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_tbo);
}
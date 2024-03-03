#include "include/gl_texture.h"

#include <GL/glew.h>

gl_texture::gl_texture(int width, int height, unsigned char* data)
{
    glGenTextures(1, &m_id); 

    // Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, m_id);
    auto internal_format = GL_RGBA;
    auto format = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

gl_texture::~gl_texture()
{
    glDeleteTextures(1, &m_id);
}

void gl_texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

unsigned int gl_texture::get_id() { return m_id; }
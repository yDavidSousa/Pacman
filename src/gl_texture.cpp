#include "include/gl_texture.h"

#include <GL/glew.h>

gl_texture::gl_texture()
{
    glGenTextures(1, &buffer_id); 
}

gl_texture::~gl_texture()
{
    glDeleteTextures(1, &buffer_id);
}

void gl_texture::set_info()
{
    glBindTexture(GL_TEXTURE_2D, buffer_id);

    // wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void gl_texture::set_data(int width, int height, unsigned char* data)
{
    glBindTexture(GL_TEXTURE_2D, buffer_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void gl_texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, buffer_id);
}
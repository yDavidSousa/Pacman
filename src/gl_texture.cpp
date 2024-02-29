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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void gl_texture::set_data(int width, int height, unsigned char* data)
{
    glBindTexture(GL_TEXTURE_2D, buffer_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void gl_texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, buffer_id);
}
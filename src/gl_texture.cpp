#include "include/gl_texture.h"


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
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

void gl_texture::set_data(int width, int height, bool alpha, unsigned char* data)
{
    glBindTexture(GL_TEXTURE_2D, buffer_id);

    auto internal_format = alpha ? GL_RGBA : GL_RGB;
    auto format = alpha ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void gl_texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, buffer_id);
}

void load_texture(const char* path, bool alpha, std::unique_ptr<gl_texture> &texture)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if(data)
    {
        texture->set_data(width, height, alpha, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
#define STB_IMAGE_IMPLEMENTATION

#include "include/gl_renderer.h"

#include <stb_image.h>
#include <GL/glew.h>

gl_renderer::gl_renderer()
{
    if(glewInit() != GLEW_OK)
    {
        return;
    }

    glEnable(GL_TEXTURE_2D);
}

gl_renderer::~gl_renderer()
{
}

std::unique_ptr<gl_shader> gl_renderer::create_shader(const char* vert_source, const char* frag_source)
{
    auto shader_instance = std::make_unique<gl_shader>(vert_source, frag_source);
    return shader_instance;
}

std::unique_ptr<gl_mesh> gl_renderer::create_mesh(const float* vertices, const unsigned long vert_length, const unsigned int* indices, const unsigned long ind_length)
{
    auto mesh_instance = std::make_unique<gl_mesh>(vertices, vert_length, indices, ind_length);
    return mesh_instance;
}

std::unique_ptr<gl_texture> gl_renderer::create_texture(const char* path)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
    if(!data)
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    auto texture_instance = std::make_unique<gl_texture>(width, height, channels, data);
    stbi_image_free(data);
    return texture_instance;
}
#include "include/gl_renderer.h"

#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

gl_renderer::gl_renderer()
{
    if(glewInit() != GLEW_OK)
    {
        return;
    }
}

std::unique_ptr<gl_shader> gl_renderer::create_shader(const char* vert_source, const char* frag_source)
{
    auto shader_instance = std::make_unique<gl_shader>(vert_source, frag_source);
    return shader_instance;
}

std::unique_ptr<gl_mesh> gl_renderer::create_mesh(const mesh_data& data)
{
    auto mesh_instance = std::make_unique<gl_mesh>(data.vertices, data.indices, data.tex_coords);
    return mesh_instance;
}

std::unique_ptr<gl_texture> gl_renderer::create_texture(const char* path)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if(!data)
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    auto texture_instance = std::make_unique<gl_texture>(width, height, data);
    stbi_image_free(data);
    return texture_instance;
}

void gl_renderer::push_quad(const glm::vec2 position, const glm::vec2 size, const glm::vec4 color)
{
}

void gl_renderer::push_quad(const glm::vec2 position, const glm::vec2 size, const unsigned int texture_id)
{
}

void gl_renderer::render()
{
}
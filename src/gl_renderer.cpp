#include "include/gl_renderer.h"

#include <GL/glew.h>

gl_renderer::gl_renderer()
{
    if(glewInit() != GLEW_OK)
    {
        return;
    }
}

std::unique_ptr<gl_shader> gl_renderer::create_shader()
{
    auto shader_instance = std::make_unique<gl_shader>();
    return shader_instance;
}

std::unique_ptr<gl_mesh> gl_renderer::create_mesh()
{
    auto mesh_instance = std::make_unique<gl_mesh>();
    return mesh_instance;
}

std::unique_ptr<gl_texture> gl_renderer::create_texture()
{
    auto texture_instance = std::make_unique<gl_texture>();
    return texture_instance;
}

void gl_renderer::render()
{

}
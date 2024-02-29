#ifndef PACMAN_GL_TEXTURE_H
#define PACMAN_GL_TEXTURE_H

#include <iostream>

class gl_texture
{
    public:
    gl_texture();
    ~gl_texture();

    void set_info();
    void set_data(int width, int height, bool alpha, unsigned char* data);
    void bind();

    private:
    unsigned int buffer_id;
};

void load_texture(const char* path, bool alpha, std::unique_ptr<gl_texture> &texture);

#endif
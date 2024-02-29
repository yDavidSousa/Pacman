#ifndef PACMAN_GL_TEXTURE_H
#define PACMAN_GL_TEXTURE_H

class gl_texture
{
    public:
    gl_texture();
    ~gl_texture();

    void set_info();
    void set_data(int width, int height, unsigned char* data);
    void bind();

    private:
    unsigned int buffer_id;
};

#endif
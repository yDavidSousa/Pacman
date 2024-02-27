#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "mesh.h"

mesh::mesh(std::vector<float> vertices)
{
    vb_data = vertices;
}

mesh::~mesh()
{
    glDeleteVertexArrays(1, &va_id);
    glDeleteBuffers(1, &vb_id);
}

void mesh::bind()
{
    glGenVertexArrays(1, &va_id);
    glBindVertexArray(va_id);

    glGenBuffers(1, &vb_id);
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);

    glBufferData(GL_ARRAY_BUFFER, vb_data.size() * sizeof(float), vb_data.data(), GL_STATIC_DRAW);
}

void mesh::draw()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
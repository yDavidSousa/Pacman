#include "include/gl_mesh.h"

#include <GL/glew.h>
#include <iostream>

gl_mesh::gl_mesh(const float* vertices, const unsigned long num_vertices, const unsigned int* indices, const unsigned long num_indices) : vertices_length(num_vertices), indices_length(num_indices)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    if(num_vertices)
    {
        glGenBuffers(1, &vbo_vertices);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
        glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(float), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    if(num_indices)
    {
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glBindVertexArray(0);
}

gl_mesh::~gl_mesh()
{
    if (ibo) glDeleteBuffers(1, &ibo);
    if (vbo_vertices) glDeleteBuffers(1, &vbo_vertices);
    glDeleteVertexArrays(1, &vao);
}

void gl_mesh::draw()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, indices_length, GL_UNSIGNED_INT, 0);
}
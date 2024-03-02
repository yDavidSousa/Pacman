#include "include/gl_mesh.h"

#include <GL/glew.h>

gl_mesh::gl_mesh()
{
    glGenVertexArrays(1, &va_id);
    glGenBuffers(1, &vb_id);
    glGenBuffers(1, &eb_id);
}

gl_mesh::~gl_mesh()
{
    glDeleteVertexArrays(1, &va_id);
    glDeleteBuffers(1, &vb_id); 
    glDeleteBuffers(1, &eb_id);
}

void gl_mesh::set_vertices(std::vector<float> vertices)
{
    m_vertices = vertices;

    //fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);
    const auto buffer_size = static_cast<GLsizeiptr>(m_vertices.size() * sizeof(float));
    glBufferData(GL_ARRAY_BUFFER, buffer_size, m_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gl_mesh::set_indices(std::vector<unsigned int> indices)
{
    m_indices = indices;

    //fill buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb_id);
    const auto buffer_size = static_cast<GLsizeiptr>(m_indices.size() * sizeof(unsigned int));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, m_indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void gl_mesh::bind()
{
    glBindVertexArray(va_id);
    glBindBuffer(GL_ARRAY_BUFFER, vb_id);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void gl_mesh::draw()
{
    glBindVertexArray(va_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
#include "include/gl_mesh.h"

#include <GL/glew.h>

mesh_data::mesh_data(){}

mesh_data::mesh_data(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> tex_coords)
 : vertices(vertices), indices(indices), tex_coords(tex_coords)
{
}

const mesh_data mesh_data::get_primitive_quad()
{
    mesh_data quad(quad_vertices, quad_indices, quad_text_coords);
    return quad;
}

gl_mesh::gl_mesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> tex_coords)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const unsigned int buffer_usage = GL_STATIC_DRAW;

    int num_vertices = vertices.size();
    if(num_vertices)
    {
        glGenBuffers(1, &vbo_vertices);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
        glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(float), vertices.data(), buffer_usage);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    int num_indices = indices.size();
    if(num_indices)
    {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(unsigned int), indices.data(), buffer_usage);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    int num_tex_coords = tex_coords.size();
    if(num_tex_coords)
    {
        glGenBuffers(1, &vbo_tex_coords);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_tex_coords);
        glBufferData(GL_ARRAY_BUFFER, num_tex_coords * sizeof(float), tex_coords.data(), buffer_usage);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glGenBuffers(1, &instance_bo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_bo);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*) 0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*) (1 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*) (2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*) (3 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

gl_mesh::~gl_mesh()
{
    if (ebo) glDeleteBuffers(1, &ebo);
    if (instance_bo) glDeleteBuffers(1, &instance_bo);
    if (vbo_vertices) glDeleteBuffers(1, &vbo_vertices);
    if (vbo_tex_coords) glDeleteBuffers(1, &vbo_tex_coords);
    glDeleteVertexArrays(1, &vao);
}

void gl_mesh::draw(const std::vector<glm::mat4>& models)
{
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, instance_bo);
    glBufferData(GL_ARRAY_BUFFER, models.size() * sizeof(glm::mat4), models.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, models.size());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
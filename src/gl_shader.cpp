#include "include/gl_shader.h"

#include <GL/glew.h>

#include <iostream>

gl_shader::gl_shader(const char* vert_source, const char* frag_source)
{
    m_program = glCreateProgram();

    int success;
    char infoLog[512];

    //Compile Vertex Shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vert_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Compile Fragment Shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &frag_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Link
    glAttachShader(m_program, vertex_shader);
    glAttachShader(m_program, fragment_shader);
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //FIND UNIFORMS HERE

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

gl_shader::~gl_shader()
{
    glDeleteProgram(m_program);
}

void gl_shader::use()
{
    glUseProgram(m_program);
}

void gl_shader::set_uniform_mat4(const char *name, glm::mat4 value)
{
    unsigned int location = glGetUniformLocation(m_program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
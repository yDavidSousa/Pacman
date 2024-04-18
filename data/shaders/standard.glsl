#vert
#version 330 core

layout (location = 0) in vec2 a_vert;
layout (location = 1) in vec2 a_tex;

out vec2 v_tex;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(a_vert.xy, 0.0f, 1.0f);
    v_tex = a_tex;
}

#frag
#version 330 core

uniform vec4 u_color;
uniform sampler2D u_texture;

in vec2 v_tex;

out vec4 o_color;

void main()
{
    o_color = texture(u_texture, v_tex) * u_color;
}
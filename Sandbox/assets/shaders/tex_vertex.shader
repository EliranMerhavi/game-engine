#version 410 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_tex_coord;
layout (location = 3) in int a_tex_index;

out vec4 v_color;
out vec2 v_tex_coord;
flat out int v_tex_index;

uniform mat4 u_mvp;

void main()
{
    v_color = a_color;
    v_tex_coord = a_tex_coord;
    v_tex_index = a_tex_index;
    gl_Position = u_mvp * a_position;
}
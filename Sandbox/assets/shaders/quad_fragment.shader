#version 410 core

layout(location = 0) out vec4 o_color;
  
in vec4 v_color;
in vec2 v_tex_coord;
flat in int v_tex_index;

uniform sampler2D u_textures[32];

void main()
{
    o_color = v_color * texture(u_textures[v_tex_index], v_tex_coord);
}
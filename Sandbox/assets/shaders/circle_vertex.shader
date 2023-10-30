#version 410 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_local_position;

out	vec4 v_color;
out vec2 v_local_position;

uniform mat4 u_mvp;

void main()
{
	v_color				= a_color;
	v_local_position    = a_local_position;

	gl_Position = u_mvp * a_position;
}
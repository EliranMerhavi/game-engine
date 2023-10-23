#version 410 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in float a_radius;
layout(location = 3) in vec2 a_center;

out	vec4 v_color;
out vec2 v_position;
out vec2 v_center;
flat out float v_radius;


uniform mat4 u_mvp;

void main()
{
	v_color	    = a_color;
	v_position  = a_position;
	v_center    = a_center;
	v_radius    = a_radius;

	gl_Position = u_mvp * vec4(a_position, 1.0, 1.0);
}
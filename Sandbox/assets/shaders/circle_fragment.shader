#version 410 core

layout(location = 0) out vec4 o_color;

in vec4 v_color;
in vec2 v_position;
in vec2 v_center;
flat in float v_radius;

void main()
{
	float dist = v_radius - length(v_position - v_center);

	dist = step(0.0, dist);

	o_color = dist * v_color;
}
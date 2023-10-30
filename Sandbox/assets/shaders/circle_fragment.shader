#version 410 core

layout(location = 0) out vec4 o_color;

in vec4 v_color;
in vec2 v_local_position;

void main()
{
	float dist = 0.5f - length(v_local_position);

	dist = step(0.0, dist);
	if (dist == 0.0)
		discard;

	o_color = v_color;
	o_color.a *= dist;
}
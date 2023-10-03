#pragma once
#define GLEW_STATIC

#include "line2D.h"
#include "shader.h"

namespace renderer2D
{
	void init();
	bool has_initialized();
	void shutdown();

	void set_camera(const glm::mat4& camera);
	void set_color(const glm::f32vec4& color);
	void set_color(float r, float g, float b, float a);

	void draw_quad(float x, float y, float w, float h);
	// void draw_circle(float x, float y, float radius);
	void draw_line(const line2D& line);
	// void draw_texture(const char* filepath, float x, float y, float w, float h);

	void bind_default_shader();

	void render_quads();
	void render_lines();
	// void render_circles();

	void render();
	void clear();
}


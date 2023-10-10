#pragma once
#define GLEW_STATIC

#include <glm/glm.hpp>
#include "shader.h"

namespace renderer2D
{
	void init();
	bool has_initialized();
	void shutdown();

	void set_camera(const glm::mat4& camera);
	void set_color(const glm::f32vec4& color);
	void set_color(float r, float g, float b, float a);

	// void draw_circle(float x, float y, float radius);
	void rotated_quad(float x, float y, float w, float h, float degrees);
	void quad(float x, float y, float w, float h);
	void line(const glm::f32vec2& from, const glm::f32vec2& to);
	void texture(uint32_t tex_index, float x, float y, float w, float h);
	
	
	void bind_default_shader();

	void render();
	void clear();
}


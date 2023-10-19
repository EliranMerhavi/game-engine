#pragma once
#define GLEW_STATIC

#include <glm/glm.hpp>
#include "shader.h"
#include "orthographic_camera.h"

namespace renderer2D
{
	void init();
	bool has_initialized();
	void shutdown();

	
	void set_camera(const game_engine::orthographic_camera& camera);
	void set_color(const glm::f32vec4& color);
	void set_color(float r, float g, float b, float a);

	void circle(float x, float y, float radius);
	void line(const glm::f32vec2& from, const glm::f32vec2& to);

	void rotated_quad(float x, float y, float w, float h, float degrees);
	void rotated_quad(const glm::f32vec2& position, const glm::f32vec2& dimensions, float degrees);
	
	void quad(float x, float y, float w, float h);
	void quad(const glm::f32vec2& position, const glm::f32vec2& dimensions);
	void quad(const glm::f32mat4& transform);


	
	void texture(uint32_t tex_index, float x, float y, float w, float h);
	void texture(uint32_t tex_index, const glm::f32vec2& position, const glm::f32vec2& dimensions);
	void texture(uint32_t tex_index, const glm::f32mat4& transform);

	
	void bind_default_shader();

	void flush();
	void clear();
}


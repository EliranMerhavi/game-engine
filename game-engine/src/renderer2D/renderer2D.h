#pragma once
#define GLEW_STATIC

#include <glm/glm.hpp>
#include <array>
#include "shader.h"
#include "resource/resources.h"

namespace renderer2D
{
	void init();
	bool has_initialized();
	void shutdown();

	void set_camera(const glm::f32mat4& camera);
	void set_color(const glm::f32vec4& color);
	void set_color(float r, float g, float b, float a);
	
	void line(const glm::f32vec2& from, const glm::f32vec2& to);

	void circle(float x, float y, float radius);
	void circle(const glm::f32mat4& transform);
	void circle(const glm::f32mat4& transform, const glm::f32vec4& color);


	void rotated_quad(float x, float y, float w, float h, float degrees);
	void rotated_quad(const glm::f32vec2& position, const glm::f32vec2& dimensions, float degrees);
	void rotated_quad(const glm::f32mat4& transform, float degrees);

	void quad(float x, float y, float w, float h);
	void quad(const glm::f32vec2& position, const glm::f32vec2& dimensions);
	void quad(const glm::f32mat4& transform);
	void quad(const glm::f32mat4& transform, const glm::f32vec4& color, uint32_t tex_id, const std::array<glm::f32vec2, 4>& tex_coords);



	void create_texture(uint32_t& tex_id, uint8_t* data, int width, int height);
	void delete_texture(uint32_t tex_id);

	const resource::texture_t& white_texture();
	const texture_coords_t& default_texture_coords();

	void flush();
	void clear();
}


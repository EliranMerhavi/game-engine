#include "pch.h"
#include "renderer2D.h"
#include "shader.h"
#include "math/math.h"
#include "glm/gtc/matrix_transform.hpp"

namespace renderer2D
{
	bool is_initialized = false;

	struct circle_vertex {
		glm::f32vec4 position;
		float color[4];
		glm::f32vec2 local_position;
	};

	struct line_vertex {
		glm::f32vec4 position;
		float color[4];
	};

	struct quad_vertex {
		glm::f32vec4 position;
		float color[4];
		glm::f32vec2 tex_coords;
		uint32_t tex_index;
	};

	const size_t max_tex_count{ 32 };
	const size_t max_quads_count{ 20000 };
	const size_t max_quads_vertices{ max_quads_count * 4 };
	const size_t max_quads_indices{ max_quads_count * 6 };
	
	
	const size_t max_lines_count{ 20000 };
	const size_t max_lines_vertices{ max_lines_count * 2 };
	const size_t max_lines_indices{ max_lines_count * 2 };

	const size_t max_circles_count{ 20000 };
	const size_t max_circles_vertices{ max_quads_count * 4 };
	const size_t max_circles_indices{ max_quads_count * 6 };

	glm::f32vec4 _color{ 1.0f,1.0f,1.0f,1.0f };

	std::unique_ptr<opengl::shader> quad_shader, circle_shader;

	uint32_t quads_count{ 0 }, lines_count{ 0 }, tex_count{ 1 }, circle_count{ 0 };
	uint32_t quad_vbo, quad_ibo, quad_vao,
			 circle_vbo, circle_ibo, circle_vao,
			 line_vbo, line_vao;
	
	glm::f32vec4 s_quad_vertices[4];
	texture_coords_t s_texture_coords;
	uint32_t s_textures[32];
	resource::texture_t s_white_texture;

}

void renderer2D::set_camera(const glm::f32mat4& camera)
{
	quad_shader->bind();
	quad_shader->set_uniform_mat_4f("u_mvp", camera);
	circle_shader->bind();
	circle_shader->set_uniform_mat_4f("u_mvp", camera);
}

void renderer2D::init()
{
	if (is_initialized)
		throw std::exception("renderer2D has already been initialized");
	
	glEnable(GL_TEXTURE_2D);
	
	quad_shader = std::make_unique<opengl::shader>("assets/shaders/quad_vertex.shader", "assets/shaders/quad_fragment.shader");
	circle_shader = std::make_unique<opengl::shader>("assets/shaders/circle_vertex.shader", "assets/shaders/circle_fragment.shader");
	
	int n = std::max(max_quads_indices, max_circles_indices);

	uint32_t* indices = new uint32_t[n];
	uint32_t offset = 0;

	for (size_t i = 0; i < n; i += 6, offset += 4)
	{
		indices[i]	   = offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = offset;
	}

	// ------------------------------------------
	// initialization of the quad vao
	// ------------------------------------------
	glCreateVertexArrays(1, &quad_vao);
	glBindVertexArray(quad_vao);

	glCreateBuffers(1, &quad_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
	glBufferData(GL_ARRAY_BUFFER, max_quads_vertices * sizeof(quad_vertex), nullptr, GL_DYNAMIC_DRAW);
	
	glCreateBuffers(1, &quad_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_quads_indices * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(quad_vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(quad_vertex), (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(quad_vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(quad_vertex), (const void*)offsetof(quad_vertex, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(quad_vertex::tex_coords) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(quad_vertex), (const void*)offsetof(quad_vertex, tex_coords));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, sizeof(quad_vertex::tex_index) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(quad_vertex), (const void*)offsetof(quad_vertex, tex_index));

		
	int32_t* samplers = new int32_t[max_tex_count];

	for (int i = 0; i < max_tex_count; i++)
		samplers[i] = i;

	quad_shader->bind();
	quad_shader->set_uniform_1iv("u_textures", max_tex_count, samplers);

	// ------------------------------------------
	// initialization of the line vao
	// ------------------------------------------
	
	glCreateVertexArrays(1, &line_vao);
	glCreateBuffers(1, &line_vbo);
	glBindVertexArray(line_vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, line_vbo);
	glBufferData(GL_ARRAY_BUFFER, max_lines_vertices * sizeof(line_vertex), nullptr, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(line_vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(line_vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(line_vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(line_vertex), (const void*)offsetof(line_vertex, color));


	// ------------------------------------------
	// initialization of the circle vao
	// ------------------------------------------
	glCreateVertexArrays(1, &circle_vao);
	glBindVertexArray(circle_vao);

	glCreateBuffers(1, &circle_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
	glBufferData(GL_ARRAY_BUFFER, max_circles_vertices * sizeof(circle_vertex), nullptr, GL_DYNAMIC_DRAW);

	glCreateBuffers(1, &circle_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circle_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_circles_indices * sizeof(uint32_t), indices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(circle_vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(circle_vertex), (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(circle_vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(circle_vertex), (const void*)offsetof(circle_vertex, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(circle_vertex::local_position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(circle_vertex), (const void*)offsetof(circle_vertex, local_position));
	
	// ------------------------------------------

	s_quad_vertices[0] = glm::f32vec4{ -0.5f, -0.5f, 0.0f, 1.0f };
	s_quad_vertices[1] = glm::f32vec4{ -0.5f,  0.5f, 0.0f, 1.0f };
	s_quad_vertices[2] = glm::f32vec4{  0.5f,  0.5f, 0.0f, 1.0f };
	s_quad_vertices[3] = glm::f32vec4{  0.5f, -0.5f, 0.0f, 1.0f };
	
	s_texture_coords[0] = glm::f32vec2{ 1.0f, 1.0f };
	s_texture_coords[1] = glm::f32vec2{ 1.0f, 0.0f };
	s_texture_coords[2] = glm::f32vec2{ 0.0f, 0.0f };
	s_texture_coords[3] = glm::f32vec2{ 0.0f, 1.0f };
	
	quad_shader->bind();

	s_white_texture.m_is_parent = true;
	s_white_texture.m_parent_data = new resource::texture_t::parent_data_t{ .is_deleted = false, .flip_verticaly = false };
	s_white_texture.m_dimensions = { 1, 1 };
	s_white_texture.m_coords = default_texture_coords();

	uint32_t data = 0xFFFFFFFF;
	renderer2D::create_texture(s_white_texture.m_renderer_id, (uint8_t*)&data, 1, 1);
	glBindTextureUnit(0, s_white_texture.id());
	
	delete[] samplers;
	delete[] indices;
	is_initialized = true;
}

bool renderer2D::has_initialized()
{
	return is_initialized;
}

void renderer2D::shutdown()
{
	glDeleteBuffers(1, &quad_vbo);
	glDeleteBuffers(1, &line_vbo);
	glDeleteBuffers(1, &circle_vbo);

	glDeleteBuffers(1, &quad_ibo);
	glDeleteBuffers(1, &circle_ibo);

	glDeleteVertexArrays(1, &quad_vao);
	glDeleteVertexArrays(1, &line_vao);
	glDeleteVertexArrays(1, &circle_vao);

	s_white_texture.delete_texture();
}

void renderer2D::set_color(float r, float g, float b, float a)
{
	set_color({ r, g, b, a });
}

void renderer2D::set_color(const glm::f32vec4& color)
{
	_color = color;
}

void renderer2D::circle(float x, float y, float radius)
{
	glm::f32mat4 transform(1.0f);

	transform = glm::translate(transform, glm::f32vec3(x, y, 0.0f));
	transform = glm::scale(transform, glm::f32vec3(radius * 2.0f, radius * 2.0f, 1.0f));

	renderer2D::circle(transform);
}

void renderer2D::circle(const glm::f32mat4& transform)
{
	circle(transform, _color);
}

void renderer2D::circle(const glm::f32mat4& transform, const glm::f32vec4& color)
{
	if (circle_count == max_circles_count)
		flush();

	circle_vertex vertices[] = {
		{transform * s_quad_vertices[0], color.r, color.g, color.b, color.a, s_quad_vertices[0]},
		{transform * s_quad_vertices[1], color.r, color.g, color.b, color.a, s_quad_vertices[1]},
		{transform * s_quad_vertices[2], color.r, color.g, color.b, color.a, s_quad_vertices[2]},
		{transform * s_quad_vertices[3], color.r, color.g, color.b, color.a, s_quad_vertices[3]}
	};

	glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, circle_count * 4 * sizeof(circle_vertex), sizeof(vertices), vertices);
	circle_count++;
}

void renderer2D::line(const glm::f32vec2& from, const glm::f32vec2& to)
{
	if (lines_count == max_lines_count)
		flush();
	
	line_vertex vertices[] = {
		{{from, 0.0f, 1.0f}, _color.r, _color.g, _color.b, _color.a},
		{{to, 0.0f, 1.0f},   _color.r, _color.g, _color.b, _color.a}
	};
	
	glBindBuffer(GL_ARRAY_BUFFER, line_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, lines_count * 2 * sizeof(line_vertex), sizeof(vertices), vertices);
	lines_count++;
}

void renderer2D::rotated_quad(float x, float y, float w, float h, float degrees)
{
	renderer2D::rotated_quad({ x, y }, { w, h }, degrees);
}

void renderer2D::rotated_quad(const glm::f32vec2& position, const glm::f32vec2& dimensions, float degrees)
{
	glm::f32mat4 transform(1.0f);

	transform = glm::translate(transform, glm::f32vec3(position, 0.0f));
	transform = glm::scale(transform, glm::f32vec3(dimensions, 1.0f));
	transform = glm::rotate(transform, glm::radians(degrees), glm::f32vec3(0, 0, 1));

	renderer2D::quad(transform);
}

void renderer2D::rotated_quad(const glm::f32mat4& transform, float degrees)
{
	renderer2D::quad(glm::rotate(transform, glm::radians(degrees), glm::f32vec3(0, 0, 1)));
}

void renderer2D::quad(float x, float y, float w, float h)
{
	renderer2D::quad({x, y}, {w, h});
}

void renderer2D::quad(const glm::f32vec2& position, const glm::f32vec2& dimensions)
{
	glm::f32mat4 transform(1.0f);
	
	transform = glm::translate(transform, glm::f32vec3(position, 0.0f));
	transform = glm::scale(transform, glm::f32vec3(dimensions, 1.0f));

	renderer2D::quad(transform);
}

void renderer2D::quad(const glm::f32mat4& transform)
{
	renderer2D::quad(transform, _color, white_texture().id(), default_texture_coords());
}

void renderer2D::quad(const glm::f32mat4& transform, const glm::f32vec4& color, uint32_t tex_id, const std::array<glm::f32vec2, 4>& tex_coords)
{
	if (quads_count == max_quads_count || tex_count == max_tex_count)
		flush();

	int i;

	for (i = 1; i < tex_count && (s_textures[i] != tex_id); i++)
		;
	
	quad_vertex vertices[] = {
		// positions					  // colors							  // texture coords
		{transform * s_quad_vertices[0],  color.r, color.g, color.b, color.a, tex_coords[0], i}, // top right
		{transform * s_quad_vertices[1],  color.r, color.g, color.b, color.a, tex_coords[1], i}, // bottom right
		{transform * s_quad_vertices[2],  color.r, color.g, color.b, color.a, tex_coords[2], i}, // bottom left
		{transform * s_quad_vertices[3],  color.r, color.g, color.b, color.a, tex_coords[3], i}  // top left 
	};

	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, quads_count * 4 * sizeof(quad_vertex), sizeof(vertices), vertices);
	quads_count++;

	quad_shader->bind();

	if (i == tex_count) {
		glBindTextureUnit(tex_count, tex_id);
		s_textures[i] = tex_id;
		tex_count++;
	}
}


void renderer2D::create_texture(uint32_t& tex_id, uint8_t* data, int width, int height)
{
	quad_shader->bind();
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, s_white_texture.id());
}

void renderer2D::delete_texture(uint32_t tex_id)
{
	glDeleteTextures(1, &tex_id);
}

const resource::texture_t& renderer2D::white_texture()
{
	return s_white_texture;
}

const renderer2D::texture_coords_t& renderer2D::default_texture_coords()
{
	return s_texture_coords;
}

void renderer2D::flush()
{
	if (quads_count)
	{
		quad_shader->bind();
		glBindVertexArray(quad_vao);
		glDrawElements(GL_TRIANGLES, quads_count * 6, GL_UNSIGNED_INT, nullptr);
		quads_count = 0;
		tex_count = 1;
	}
	
	if (circle_count) 
	{
		circle_shader->bind();
		glBindVertexArray(circle_vao);
		glDrawElements(GL_TRIANGLES, circle_count * 6, GL_UNSIGNED_INT, nullptr);
		circle_count = 0;
	}

	if (lines_count)
	{
		glBindVertexArray(line_vao);
		glDrawArrays(GL_LINES, 0, lines_count * 2);
		lines_count = 0;
	}
}

void renderer2D::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
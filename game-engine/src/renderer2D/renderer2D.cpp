#include "pch.h"
#include "renderer2D.h"
#include "shader.h"
#include "math/math.h"

namespace renderer2D
{
	bool is_initialized = false;

	struct vertex {
		float position[2];
		float color[4];
	};

	struct circle_vertex {
		float position[2];
		float color[4];
		float radius;
		float center[2];
	};


	struct tex_vertex {
		float position[2];
		float color[4];
		float tex_coords[2];
		uint32_t tex_index;
	};

	const size_t max_quads_count{ 1000 };
	const size_t max_quads_vertices{ max_quads_count * 4 };
	const size_t max_quads_indices{ max_quads_count * 6 };
	
	const size_t max_tex_count{ 32 };
	const size_t max_tex_vertices{ max_quads_count * 4 };
	const size_t max_tex_indices{ max_quads_count * 6 };

	const size_t max_lines_count{ 1000 };
	const size_t max_lines_vertices{ max_lines_count * 2 };
	const size_t max_lines_indices{ max_lines_count * 2 };

	const size_t max_circles_count{ 1000 };
	const size_t max_circles_vertices{ max_lines_count * 2 };
	const size_t max_circles_indices{ max_lines_count * 2 };


	glm::f32vec4 _color{ 1.0f,1.0f,1.0f,1.0f };
	std::unique_ptr<opengl::shader> default_shader, default_tex_shader, default_circle_shader;

	uint32_t quads_count{ 0 }, lines_count{ 0 }, tex_count{ 0 }, circle_count{ 0 };
	uint32_t quad_vbo, quad_ibo, quad_vao,
			 tex_vbo, tex_ibo, tex_vao,
			 circle_vbo, circle_ibo, circle_vao,
			 line_vbo, line_vao;

	void flush_quads();
	void flush_lines();
	void flush_textures();
	void flush_circles();
}


void renderer2D::set_camera(const glm::mat4& camera)
{
	default_shader->bind();
	default_shader->set_uniform_mat_4f("u_mvp", camera);
	default_tex_shader->bind();
	default_tex_shader->set_uniform_mat_4f("u_mvp", camera);
	default_circle_shader->bind();
	default_circle_shader->set_uniform_mat_4f("u_mvp", camera);
}

void renderer2D::init()
{
	if (is_initialized)
		throw std::exception("renderer2D has already been initialized");
	
	glEnable(GL_TEXTURE_2D);
	
	default_tex_shader = std::make_unique<opengl::shader>("assets/shaders/tex_vertex.shader", "assets/shaders/tex_fragment.shader");
	default_shader = std::make_unique<opengl::shader>("assets/shaders/vertex.shader", "assets/shaders/fragment.shader");
	default_circle_shader = std::make_unique<opengl::shader>("assets/shaders/circle_vertex.shader", "assets/shaders/circle_fragment.shader");
	default_shader->bind();
	

	int n = std::max(max_quads_indices, std::max(max_tex_indices, max_circles_indices));

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
	glBufferData(GL_ARRAY_BUFFER, max_quads_vertices * sizeof(vertex), nullptr, GL_DYNAMIC_DRAW);
	
	glCreateBuffers(1, &quad_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_quads_indices * sizeof(uint32_t), indices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex, color));
	
	// ------------------------------------------
	// initialization of the line vao
	// ------------------------------------------
	glCreateVertexArrays(1, &line_vao);
	glCreateBuffers(1, &line_vbo);
	glBindVertexArray(line_vao);

	glBindBuffer(GL_ARRAY_BUFFER, line_vbo);
	glBufferData(GL_ARRAY_BUFFER, max_lines_vertices * sizeof(vertex), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vertex) / sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vertex) / sizeof(float), (const void*)offsetof(vertex, color));
	
	// ------------------------------------------
	// initialization of the texture vao
	// ------------------------------------------
	glCreateVertexArrays(1, &tex_vao);
	glBindVertexArray(tex_vao);

	glCreateBuffers(1, &tex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	glBufferData(GL_ARRAY_BUFFER, max_tex_vertices * sizeof(tex_vertex), nullptr, GL_DYNAMIC_DRAW);

	glCreateBuffers(1, &tex_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tex_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_tex_indices * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(tex_vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(tex_vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(tex_vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(tex_vertex), (const void*)offsetof(vertex, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(tex_vertex::tex_coords) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(tex_vertex), (const void*)offsetof(tex_vertex, tex_coords));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, sizeof(tex_vertex::tex_index), GL_UNSIGNED_INT, GL_FALSE, sizeof(tex_vertex), (const void*)offsetof(tex_vertex, tex_index));


	int32_t* samplers = new int32_t[max_tex_count];

	for (int i = 0; i < max_tex_count; i++)
		samplers[i] = i;

	default_tex_shader->bind();
	default_tex_shader->set_uniform_1iv("u_textures", max_tex_count, samplers);

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
	glVertexAttribPointer(2, sizeof(circle_vertex::radius), GL_FLOAT, GL_FALSE, sizeof(circle_vertex), (const void*)offsetof(circle_vertex, radius));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(circle_vertex::radius), GL_FLOAT, GL_FALSE, sizeof(circle_vertex), (const void*)offsetof(circle_vertex, radius));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, sizeof(circle_vertex::center) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(circle_vertex), (const void*)offsetof(circle_vertex, center));
	// ------------------------------------------


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
	glDeleteBuffers(1, &tex_vbo);
	glDeleteBuffers(1, &circle_vbo);

	glDeleteBuffers(1, &quad_ibo);
	glDeleteBuffers(1, &tex_ibo);
	glDeleteBuffers(1, &circle_ibo);

	glDeleteVertexArrays(1, &quad_vao);
	glDeleteVertexArrays(1, &line_vao);
	glDeleteVertexArrays(1, &tex_vao);
	glDeleteVertexArrays(1, &circle_vao);
}

void renderer2D::set_color(const glm::f32vec4& color)
{
	_color = color;
}

void renderer2D::set_color(float r, float g, float b, float a)
{
	_color = { r, g, b, a };
}

void renderer2D::circle(float x, float y, float radius)
{
	if (circle_count == max_circles_count)
		flush_circles();

	circle_vertex vertices[] = {
		{x - radius, y - radius, _color.r, _color.g, _color.b, _color.a, radius, x, y},
		{x - radius, y + radius, _color.r, _color.g, _color.b, _color.a, radius, x, y},
		{x + radius, y + radius, _color.r, _color.g, _color.b, _color.a, radius, x, y},
		{x + radius, y - radius, _color.r, _color.g, _color.b, _color.a, radius, x, y}
	};

	glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, circle_count * 4 * sizeof(circle_vertex), sizeof(vertices), vertices);
	circle_count++;
}


void renderer2D::rotated_quad(float x, float y, float w, float h, float degrees)
{
	glm::f32vec2	v1 = {x, y + h},
					v2 = {x, y},
					v3 = {x + w, y},
					v4	= { x + w, y + h },
					origin = { x + w / 2, y + h / 2};
	
	math::vec::rotate(v1, degrees, origin);
	math::vec::rotate(v2, degrees, origin);
	math::vec::rotate(v3, degrees, origin);
	math::vec::rotate(v4, degrees, origin);
	
	vertex vertices[] = {
		{ v1.x, v1.y, _color.r, _color.g, _color.b, _color.a},
		{ v2.x, v2.y, _color.r, _color.g, _color.b, _color.a},
		{ v3.x, v3.y, _color.r, _color.g, _color.b, _color.a},
		{ v4.x, v4.y, _color.r, _color.g, _color.b, _color.a}
	};

	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, quads_count * 4 * sizeof(vertex), sizeof(vertices), vertices);

	quads_count++;
}	

void renderer2D::quad(float x, float y, float w, float h)
{
	if (quads_count == max_quads_count)
		flush_quads();

	vertex vertices[] = {
		{x	  , y + h, _color.r, _color.g, _color.b, _color.a},
		{x	  , y	 , _color.r, _color.g, _color.b, _color.a},
		{x + w, y	 , _color.r, _color.g, _color.b, _color.a},
		{x + w, y + h, _color.r, _color.g, _color.b, _color.a}
	};

	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, quads_count * 4 * sizeof(vertex), sizeof(vertices), vertices);

	quads_count++;
}

void renderer2D::line(const glm::f32vec2& from, const glm::f32vec2& to)
{
	if (lines_count == max_lines_count)
		flush_lines();

	vertex vertices[] = {
		{from.x, from.y, _color.r, _color.g, _color.b, _color.a},
		{to.x,   to.y,   _color.r, _color.g, _color.b, _color.a}
	};
	
	glBindBuffer(GL_ARRAY_BUFFER, line_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, lines_count * 2 * sizeof(vertex), sizeof(vertices), vertices);
	lines_count++;
}

void renderer2D::texture(uint32_t tex_index, float x, float y, float w, float h)
{
	if (tex_count == max_tex_count)
		flush_textures();

	tex_vertex vertices[] = {
		// positions	// colors				    // texture coords
		{x	  ,	y + h,  1.0f, 0.0f, 0.0f, _color.a,  1.0f, 1.0f, tex_count},   // top right
		{x	  ,	y	 ,  0.0f, 1.0f, 0.0f, _color.a,  1.0f, 0.0f, tex_count},   // bottom right
		{x + w,	y	 ,  0.0f, 0.0f, 1.0f, _color.a,  0.0f, 0.0f, tex_count},   // bottom left
		{x + w, y + h,  1.0f, 1.0f, 0.0f, _color.a,  0.0f, 1.0f, tex_count}    // top left 
	};
	
	default_tex_shader->bind();
	
	glBindTextureUnit(tex_count, tex_index);

	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, tex_count * 4 * sizeof(tex_vertex), sizeof(vertices), vertices);
	
	glBindVertexArray(tex_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	tex_count++;
}

void renderer2D::bind_default_shader()
{
	default_shader->bind();
}

void renderer2D::flush_quads()
{
	glBindVertexArray(quad_vao);
	glDrawElements(GL_TRIANGLES, quads_count * 6, GL_UNSIGNED_INT, nullptr);
	
	quads_count = 0;
}

void renderer2D::flush_lines()
{
	glBindVertexArray(line_vao);
	glDrawArrays(GL_LINES, 0, lines_count * 2);

	lines_count = 0;
}

void renderer2D::flush_textures()
{
	default_tex_shader->bind();
	glBindVertexArray(tex_vao);
	glDrawElements(GL_TRIANGLES, tex_count * 6, GL_UNSIGNED_INT, nullptr);

	tex_count = 0;
}

void renderer2D::flush_circles()
{
	default_circle_shader->bind();
	glBindVertexArray(circle_vao);
	glDrawElements(GL_TRIANGLES, circle_count * 6, GL_UNSIGNED_INT, nullptr);
	circle_count = 0;
}
void renderer2D::flush()
{
	default_shader->bind();
	flush_lines();
	flush_quads();
	flush_textures();
	flush_circles();
}

void renderer2D::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
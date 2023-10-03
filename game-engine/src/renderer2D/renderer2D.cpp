#include "pch.h"
#include "renderer2D.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace renderer2D
{
	bool is_initialized = false;

	struct vertex {
		float position[2];
		float color[4];
	};

	struct tex_vertex {
		float position[2];
		float color[4];
		float tex_coords[2];
	};

	const size_t max_quads_count{ 1000 };
	const size_t max_quads_vertices{ max_quads_count * 4 };
	const size_t max_quads_indices{ max_quads_count * 6 };
	
	const size_t max_tex_count{ 1000 };
	const size_t max_tex_vertices{ max_quads_count * 4 };
	const size_t max_tex_indices{ max_quads_count * 6 };

	const size_t max_lines_count{ 1000 };
	const size_t max_lines_vertices{ max_lines_count * 2 };
	const size_t max_lines_indices{ max_lines_count * 2 };


	glm::f32vec4 _color{ 1.0f,1.0f,1.0f,1.0f };
	std::unique_ptr<opengl::shader> default_shader;

	uint32_t quads_count{ 0 }, lines_count{ 0 };
	uint32_t quad_vbo, quad_ibo, quad_vao,
			 tex_vbo, tex_ibo, tex_vao,
			 line_vbo, line_vao;
}

void renderer2D::set_camera(const glm::mat4& camera)
{
	default_shader->set_uniform_mat_4f("u_mvp", camera);
}

void renderer2D::init()
{
	if (is_initialized)
		throw std::exception("renderer2D has already been initialized");
	
	glEnable(GL_TEXTURE_2D);

	default_shader = std::make_unique<opengl::shader>("assets/shaders/vertex.shader", "assets/shaders/fragment.shader");
	default_shader->bind();
	
	// ------------------------------------------
	// initialization of the quad vao
	// ------------------------------------------
	glCreateVertexArrays(1, &quad_vao);
	glCreateBuffers(1, &quad_vbo);
	glBindVertexArray(quad_vao);

	glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
	glBufferData(GL_ARRAY_BUFFER, max_quads_vertices * sizeof(vertex), nullptr, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(vertex), (const void*)offsetof(vertex, color));
	
	glCreateBuffers(1, &quad_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ibo);

	uint32_t* indices = new uint32_t[max_quads_indices];
	uint32_t offset = 0;

	for (size_t i = 0; i < max_quads_indices; i += 6, offset += 4)
	{
		indices[i] = offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = offset;
	}
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	delete[] indices;

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
	// glCreateVertexArrays(1, &tex_vao);
	// glCreateBuffers(1, &tex_vbo);
	// glCreateBuffers(1, &tex_ibo);
	// glBindVertexArray(tex_vao);
	// 
	// glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	// glBufferData(GL_ARRAY_BUFFER, max_tex_vertices * sizeof(tex_vertex), nullptr, GL_DYNAMIC_DRAW);
	// 
	// 
	// glEnableVertexAttribArray(0);
	// glVertexAttribPointer(0, sizeof(tex_vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(tex_vertex), 0);
	// glEnableVertexAttribArray(1);
	// glVertexAttribPointer(1, sizeof(tex_vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(tex_vertex), (const void*)offsetof(vertex, color));
	// glEnableVertexAttribArray(2);
	// glVertexAttribPointer(2, sizeof(tex_vertex::tex_coords) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(tex_vertex), (const void*)offsetof(tex_vertex, tex_coords));
	// 
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tex_ibo);
	// indices = new uint32_t[max_tex_indices];
	// offset = 0;
	// 
	// for (size_t i = 0; i < max_quads_indices; i += 6, offset += 4)
	// {
	// 	indices[i] = offset;
	// 	indices[i + 1] = 1 + offset;
	// 	indices[i + 2] = 2 + offset;
	// 	indices[i + 3] = 2 + offset;
	// 	indices[i + 4] = 3 + offset;
	// 	indices[i + 5] = offset;
	// }
	// 
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 
	// delete[] indices;
	// ------------------------------------------

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

	glDeleteBuffers(1, &quad_ibo);
	glDeleteBuffers(1, &tex_ibo);

	glDeleteVertexArrays(1, &quad_vao);
	glDeleteVertexArrays(1, &line_vao);
	glDeleteVertexArrays(1, &tex_vao);
}

void renderer2D::set_color(const glm::f32vec4& color)
{
	_color = color;
}

void renderer2D::set_color(float r, float g, float b, float a)
{
	_color = { r, g, b, a };
}

void renderer2D::draw_quad(float x, float y, float w, float h)
{
	if (quads_count == max_quads_count)
		render();

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

void renderer2D::draw_circle(float x, float y, float radius)
{

}

void renderer2D::draw_line(const line2D& line)
{
	if (lines_count == max_lines_count)
		render();

	glm::f32vec2 from = line.from(), to = line.to();
	glm::f32vec4 color = line.color();

	vertex vertices[] = {
		{from.x, from.y, color.r, color.g, color.b, color.a},
		{to.x,   to.y,   color.r, color.g, color.b, color.a}
	};

	glBufferSubData(GL_ARRAY_BUFFER, lines_count * 2 * sizeof(vertex), sizeof(vertices), vertices);
	lines_count++;
}

void renderer2D::draw_texture(const char* filepath, float x, float y, float w, float h)
{
	opengl::shader shader("assets/shaders/tex_vertex.shader", "assets/shaders/tex_fragment.shader");

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 4);
	std::cout << "nrChannles: " << nrChannels << '\n';
	if (!data) 
		throw std::exception("Failed to load texture");
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	tex_vertex vertices[] = {
		// positions		// colors				 // texture coords
		{ 0.5f,  0.5f,		1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f},   // top right
		{ 0.5f, -0.5f,		0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f},   // bottom right
		{-0.5f, -0.5f,		0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f},   // bottom left
		{-0.5f,  0.5f,		1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f}    // top left 
	};

	int indices[] = { 0, 1, 2, 2, 3, 0 };
	

	shader.bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.set_uniform_1i("u_texture", 0);

	glBindVertexArray(tex_vao);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void renderer2D::bind_default_shader()
{
	default_shader->bind();
}

void renderer2D::render_quads()
{
	glBindVertexArray(quad_vao);
	glDrawElements(GL_TRIANGLES, quads_count * 6, GL_UNSIGNED_INT, nullptr);
	
	quads_count = 0;
}

void renderer2D::render_lines()
{
	glBindVertexArray(line_vao);
	glDrawArrays(GL_LINES, 0, lines_count * 2);

	lines_count = 0;
}

void renderer2D::render_circles()
{

}

void renderer2D::render()
{
	bind_default_shader();
	render_lines();
	render_quads();
	render_circles();
}

void renderer2D::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
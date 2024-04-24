#include "pch.h"
#include "texture_t.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "renderer2D/renderer2D.h"

resource::texture_t::texture_t() : m_parent_data(new parent_data_t{ .is_deleted = true, .flip_verticaly = false })
{
}

resource::texture_t::texture_t(bool flip_verticaly) :
	m_renderer_id(), m_dimensions(), m_coords(renderer2D::default_texture_coords()), m_is_parent(true), m_parent_data(new parent_data_t{ .is_deleted = false, .flip_verticaly = flip_verticaly })
{
}

resource::texture_t::texture_t(uint32_t texture_id, glm::f32vec2 dimensions, const renderer2D::texture_coords_t& coords, parent_data_t* parent_data)
	: m_renderer_id(texture_id), m_dimensions(dimensions), m_coords(coords), m_is_parent(false), m_parent_data(parent_data)
{
}

void resource::texture_t::load(const void* file_data, size_t length)
{
	stbi_set_flip_vertically_on_load(m_parent_data->flip_verticaly);
	// load and generate the texture
	int32_t width, height, nrChannels;

	uint8_t* data = stbi_load_from_memory((stbi_uc*)file_data, length, &width, &height, &nrChannels, 4);

	assert(data && "failed to load texture");

	renderer2D::create_texture(m_renderer_id, data, width, height);
	m_dimensions = { width, height };
	stbi_image_free(data);
	m_parent_data->is_deleted = false;
}

resource::texture_t::~texture_t()
{
	if (m_is_parent)
		delete m_parent_data;
}

resource::texture_t resource::texture_t::sub_texture(const glm::f32vec2& start, const glm::f32vec2& sub_texture_dimenions)
{
	glm::f32vec2
		min = start / m_dimensions,
		max = (start + sub_texture_dimenions) / m_dimensions;

	return resource::texture_t{
		m_renderer_id,
		sub_texture_dimenions,
		renderer2D::texture_coords_t {
			glm::f32vec2{ max.x, max.y },
			glm::f32vec2{ max.x, min.y },
			glm::f32vec2{ min.x, min.y },
			glm::f32vec2{ min.x, max.y }
		},
		m_parent_data
	};
}

resource::texture_t& resource::texture_t::operator=(const resource::texture_t& other)
{
	this->m_renderer_id = other.m_renderer_id;
	this->m_dimensions = other.m_dimensions;
	this->m_coords = other.m_coords;

	// transfter ownership of parent texture data
	this->m_is_parent = other.m_is_parent;
	other.m_is_parent = false;

	m_parent_data = other.m_parent_data;

	return *this;
}

uint32_t resource::texture_t::id() const
{
	assert(!is_deleted());
	return m_renderer_id;
}

const glm::f32vec2& resource::texture_t::dimensions() const
{
	assert(!is_deleted());
	return m_dimensions;
}

const renderer2D::texture_coords_t& resource::texture_t::coords() const
{
	assert(!is_deleted());
	return m_coords;
}

void resource::texture_t::delete_texture()
{
	assert(!is_deleted() && "the texture already been destroyed");
	assert(m_is_parent && "can only destroy parent texture");
	renderer2D::delete_texture(m_renderer_id);
	m_parent_data->is_deleted = true;
}

bool resource::texture_t::is_deleted() const
{
	return m_parent_data->is_deleted;
}

bool resource::texture_t::is_parent() const
{
	return m_is_parent;
}


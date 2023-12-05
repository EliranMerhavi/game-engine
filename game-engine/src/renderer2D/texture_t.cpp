#include "pch.h"
#include "texture_t.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "renderer2D/renderer2D.h"

renderer2D::texture_t::texture_t() : m_is_deleted(new bool())
{
	*m_is_deleted = true;
}

renderer2D::texture_t::texture_t(const std::string& filepath, bool flip_verticaly) :
	m_renderer_id(), m_dimensions(), m_coords(renderer2D::default_texture_coords()), m_is_parent(true), m_is_deleted(new bool())
{
	stbi_set_flip_vertically_on_load(flip_verticaly);

	// load and generate the texture
	int32_t width, height, nrChannels;
	
	uint8_t* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 4);
	
	assert(data && "failed to load texture");
	
	renderer2D::create_texture(m_renderer_id, data, width, height);
	m_dimensions = { width, height };
	stbi_image_free(data);
	*m_is_deleted = false;
}

renderer2D::texture_t::texture_t(uint32_t texture_id, glm::f32vec2 dimensions, const texture_coords_t& coords, bool* is_deleted)
	: m_renderer_id(texture_id), m_dimensions(dimensions), m_coords(coords), m_is_parent(false), m_is_deleted(is_deleted)
{
}

renderer2D::texture_t::~texture_t()
{
	if (m_is_parent)
		delete m_is_deleted;
}

renderer2D::texture_t renderer2D::texture_t::sub_texture(const glm::f32vec2& start, const glm::f32vec2& sub_texture_dimenions) 
{
	glm::f32vec2 
		min = start / m_dimensions,
		max = (start + sub_texture_dimenions) / m_dimensions;

	return renderer2D::texture_t {
		m_renderer_id,
		sub_texture_dimenions,
		texture_coords_t {
			glm::f32vec2{ max.x, max.y },
			glm::f32vec2{ max.x, min.y },
			glm::f32vec2{ min.x, min.y },
			glm::f32vec2{ min.x, max.y }
		},
		m_is_deleted
	};
}

renderer2D::texture_t& renderer2D::texture_t::operator=(const renderer2D::texture_t& other)
{
	this->m_renderer_id = other.m_renderer_id;
	this->m_dimensions = other.m_dimensions;
	this->m_coords = other.m_coords;

	// transfter ownership of texture
	this->m_is_parent = other.m_is_parent;
	other.m_is_parent = false;
	
	this->m_is_deleted = other.m_is_deleted;
	
	return *this;
}

uint32_t renderer2D::texture_t::id() const
{
	assert(!is_deleted());
    return m_renderer_id;
}

const glm::f32vec2& renderer2D::texture_t::dimensions() const
{
	assert(!is_deleted());
    return m_dimensions;
}

const renderer2D::texture_coords_t& renderer2D::texture_t::coords() const
{
	assert(!is_deleted());
	return m_coords;
}

void renderer2D::texture_t::delete_texture()
{
	assert(!is_deleted() && "the texture already been destroyed");
	assert(m_is_parent && "can only destroy parent texture");
	renderer2D::delete_texture(m_renderer_id);
	*m_is_deleted = true;
}

bool renderer2D::texture_t::is_deleted() const
{
	return *m_is_deleted;
}

bool renderer2D::texture_t::is_parent() const
{
	return m_is_parent;
}


#include "pch.h"
#include "transform_t.h"


transform_t::transform_t() : transform_t({0.0f, 0.0f }, {1.0f, 1.0f}, 0.0f)
{
}

transform_t::transform_t(const glm::f32vec2& position, const glm::f32vec2& scale, float rotation) 
	: m_cache(), m_position(position), m_scale(scale), m_rotation(rotation)
{
	update_transform();
}

void transform_t::set_position(const glm::f32vec2& position)
{
	m_position = position;
	update_transform();
}

void transform_t::set_scale(const glm::f32vec2& scale)
{
	m_scale = scale;
	update_transform();
}

void transform_t::set_rotation(float rotation)
{
	m_rotation = rotation;
	update_transform();
}

glm::mat4 transform_t::transform()
{
	return m_cache;
}

void transform_t::update_transform()
{
	glm::f32mat4 transform(1.0f);

	transform = glm::translate(transform, glm::f32vec3{ m_position, 0.0f });
	transform = glm::scale(transform, glm::f32vec3{ m_scale, 1.0f });
	transform = glm::rotate(transform, glm::radians(m_rotation), glm::f32vec3{ 0, 0, 1 });

	m_cache = transform;
}

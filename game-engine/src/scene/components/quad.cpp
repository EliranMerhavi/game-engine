#include "pch.h"
#include "quad.h"

component::quad::quad(float r, float g, float b, float a, const resource::texture_t* texture)
	: m_color(r, g, b, a), m_texture(texture)
{
}

component::quad::quad(const glm::f32vec4& color, const resource::texture_t* texture)
	: m_color(color), m_texture(texture)
{
}

component::quad::quad(const resource::texture_t* texture)
	: component::quad::quad(glm::f32vec4(1), texture)
{
}

const resource::texture_t& component::quad::texture() const
{
	return *m_texture;
}

const glm::f32vec4& component::quad::color() const
{
	return m_color;
}

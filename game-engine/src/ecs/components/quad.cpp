#include "pch.h"
#include "quad.h"

component::quad::quad() : component::quad::quad({1, 1, 1, 1})
{
}

component::quad::quad(const glm::f32vec4& color) : m_color(color)
{
}

void component::quad::set_color(const glm::f32vec4& color)
{
	m_color = color;
}

const glm::f32vec4& component::quad::color() const
{
	return m_color;
}

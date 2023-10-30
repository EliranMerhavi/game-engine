#include "pch.h"
#include "circle.h"

component::circle::circle() : component::circle::circle({1, 1, 1, 1})
{
}

component::circle::circle(const glm::f32vec4& color) : m_color(color)
{
}

void component::circle::set_color(const glm::f32vec4& color)
{
	m_color = color;
}

const glm::f32vec4& component::circle::color() const
{
	return m_color;
}

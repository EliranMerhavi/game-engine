#include "pch.h"
#include "line2D.h"

renderer2D::line2D::line2D(const glm::f32vec2& from, const glm::f32vec2& to, glm::vec4 color, int lifetime) 
	: m_from(from), m_to(to), m_color(color), m_lifetime(lifetime)
{
}

int renderer2D::line2D::begin_frame()
{
	return this->m_lifetime--;
}

glm::f32vec2 renderer2D::line2D::from() const
{
	return m_from; 
}

glm::f32vec2 renderer2D::line2D::start() const
{
	return m_from;
}

glm::f32vec2 renderer2D::line2D::to() const
{
	return m_to;
}

glm::f32vec2 renderer2D::line2D::end() const
{
	return m_to;
}

glm::f32vec4 renderer2D::line2D::color() const
{
	return m_color;
}

float renderer2D::line2D::length2() const
{
	return glm::length2(m_to - m_from);
}

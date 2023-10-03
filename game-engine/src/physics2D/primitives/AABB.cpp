#include "pch.h"
#include "AABB.h"
#include "../rigid_body/rigid_body2D.h"

physics2D::AABB::AABB() : m_size{}, m_half_size(m_size * 0.5f)
{
}

physics2D::AABB::AABB(const glm::f32vec2& min, const glm::f32vec2& max) : m_size(max - min), m_half_size(m_size * 0.5f)
{
}

glm::f32vec2 physics2D::AABB::min() const
{
	return m_rigid_body.position() - m_half_size;
}

glm::f32vec2 physics2D::AABB::max() const
{
	return m_rigid_body.position() + m_half_size;
}

physics2D::rigid_body2D& physics2D::AABB::rigid_body()
{
	return this->m_rigid_body;
}

const physics2D::rigid_body2D& physics2D::AABB::rigid_body() const
{
	return this->m_rigid_body;
}

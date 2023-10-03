#include "pch.h"
#include "collision_manifold.h"

physics2D::collision_manifold::collision_manifold()
	: m_normal({0, 0}), m_contact_points(), m_depth(0.0f), m_is_colliding(false)
{
}

physics2D::collision_manifold::collision_manifold(const glm::f32vec2& normal, float depth)
	: m_normal(normal), m_contact_points(), m_depth(depth), m_is_colliding(true)
{
}

void physics2D::collision_manifold::add_contact_point(const glm::f32vec2& contact)
{
	m_contact_points.push_back(contact);
}

const glm::f32vec2& physics2D::collision_manifold::normal() const
{
	return this->m_normal;
}

const std::vector<glm::f32vec2>& physics2D::collision_manifold::contact_points() const
{
	return this->m_contact_points;
}

float physics2D::collision_manifold::depth() const
{
	return this->m_depth;
}

bool physics2D::collision_manifold::is_colliding() const
{
	return m_is_colliding;
}



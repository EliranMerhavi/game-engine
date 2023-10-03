#include "pch.h"
#include "circle.h"

physics2D::circle::circle()
    : collider2D(collider_type::CIRCLE),
    m_radius(1.0f),
    m_rigid_body()
{
}

const glm::f32vec2& physics2D::circle::center() const
{
    return this->m_rigid_body.position();
}

float& physics2D::circle::radius()
{
    return this->m_radius;
}

float physics2D::circle::radius() const
{
    return this->m_radius;
}

physics2D::rigid_body2D& physics2D::circle::rigid_body()
{
    return this->m_rigid_body;
}

const physics2D::rigid_body2D& physics2D::circle::rigid_body() const
{
    return this->m_rigid_body;
}

float physics2D::circle::get_inertia_tensor(float mass)
{
    throw std::exception("need to implement");
    return 0.0f;
}

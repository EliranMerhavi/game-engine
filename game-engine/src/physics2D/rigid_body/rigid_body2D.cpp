#include "pch.h"
#include "rigid_body2D.h"

size_t physics2D::rigid_body2D::s_rigid_body_ID = 0;

physics2D::rigid_body2D::rigid_body2D() :
    m_collider(nullptr),
    m_position(), 
    m_rotation(0.0f), 
    m_mass(0.0f),
    m_inverse_mass(0.0f),
    m_force_accum(),
    m_linear_velocity(), 
    m_angular_velocity(0.0f), 
    m_linear_damping(0.0f), 
    m_angular_damping(0.0f), 
    m_cor(1.0f),
    m_fixed_rotation(false), 
    m_id(s_rigid_body_ID++)
{
}

void physics2D::rigid_body2D::physics_update(float dt)
{
    if (!this->m_mass) return;

    // calculate linear velocity
    glm::f32vec2 acceleration = this->m_force_accum * this->m_inverse_mass;
    this->m_linear_velocity += acceleration * dt;
    // update linear position
    this->m_position += this->m_linear_velocity * dt;
    
    // synch_collision_transforms();
    this->clear_accumulators();
}

void physics2D::rigid_body2D::clear_accumulators()
{
    this->m_force_accum = { 0.0f, 0.0f };
}

void physics2D::rigid_body2D::add_force(const glm::f32vec2& force)
{
    this->m_force_accum += force;
}

void physics2D::rigid_body2D::set_transform(const glm::f32vec2& position, float rotation)
{
    this->m_position = position;
    this->m_rotation = rotation;
}

void physics2D::rigid_body2D::set_transform(const glm::f32vec2& position)
{
    this->m_position = position;
}
const physics2D::collider2D* physics2D::rigid_body2D::collider() const
{
    return this->m_collider;
}
const glm::f32vec2& physics2D::rigid_body2D::position() const
{
    return this->m_position;
}

float physics2D::rigid_body2D::rotation() const
{
    return this->m_rotation;
}

float physics2D::rigid_body2D::mass() const
{
    return this->m_mass;
}

float physics2D::rigid_body2D::inverse_mass() const
{
    return this->m_inverse_mass;
}

float physics2D::rigid_body2D::cor() const
{
    return this->m_cor;
}

const glm::f32vec2& physics2D::rigid_body2D::velocity() const
{
    return m_linear_velocity;
}

float& physics2D::rigid_body2D::cor()
{
    return this->m_cor;
}

glm::f32vec2& physics2D::rigid_body2D::velocity()
{
    return m_linear_velocity;
}

physics2D::collider2D* physics2D::rigid_body2D::collider()
{
    return m_collider;
}

bool physics2D::rigid_body2D::has_infinite_mass() const
{
    return this->m_mass == INFINITE_MASS;
}

bool physics2D::rigid_body2D::operator==(const rigid_body2D& other) const
{
    return this->m_id == other.m_id;
}

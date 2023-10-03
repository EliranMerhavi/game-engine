#include "pch.h"
#include "gravity2D.h"

physics2D::forces::gravity2D::gravity2D(const glm::f32vec2& force) : m_gravity(force)
{
}

void physics2D::forces::gravity2D::generate_force(rigid_body2D& rigid_body, float delta_time)
{
	rigid_body.add_force(this->m_gravity * rigid_body.mass());
}

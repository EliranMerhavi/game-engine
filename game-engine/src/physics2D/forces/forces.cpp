#include "pch.h"
#include "forces.h"

physics2D::forces::force_registration::force_registration(force_generator& force_gen, rigid_body2D& rigid_body)
    : m_force_generator(force_gen), m_rigid_body(rigid_body)
{
}

physics2D::forces::force_registration& physics2D::forces::force_registration::operator=(const force_registration& other)
{
    this->m_rigid_body = other.m_rigid_body;
    this->m_force_generator = other.m_force_generator;
    return *this;
}

bool physics2D::forces::force_registration::operator==(const force_registration& other) const
{
    return (&this->m_force_generator == &other.m_force_generator) && (&this->m_rigid_body == &other.m_rigid_body);
}

physics2D::forces::force_registry::force_registry() : m_registry()
{
}

void physics2D::forces::force_registry::add(rigid_body2D& rigid_body, force_generator& force_gen)
{
    this->m_registry.emplace_back(force_gen, rigid_body);
}

void physics2D::forces::force_registry::remove(rigid_body2D& rigid_body, force_generator& force_gen)
{
    this->m_registry.erase(std::find(m_registry.begin(), m_registry.end(), force_registration(force_gen, rigid_body)));
}

void physics2D::forces::force_registry::clear()
{
    this->m_registry.clear();
}

void physics2D::forces::force_registry::update_forces(float delta_time)
{
    for (auto& [force_gen, rigid_body] : m_registry)
    {
        force_gen.generate_force(rigid_body, delta_time);
    }
}

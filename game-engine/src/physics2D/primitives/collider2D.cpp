#include "pch.h"
#include "collider2D.h"

physics2D::collider2D::collider2D(collider_type type) : m_type(type), m_offset(0)
{
}

physics2D::collider_type physics2D::collider2D::type() const
{
    return m_type;
}
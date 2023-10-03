#include "pch.h"
#include "box2D.h"
#include "math/math.h"

physics2D::box2D::box2D() : m_size{}, m_half_size(m_size * 0.5f)
{
}

physics2D::box2D::box2D(const glm::f32vec2& min, const glm::f32vec2& max) : m_size(max - min), m_half_size(m_size * 0.5f)
{
}

std::vector<glm::f32vec2> physics2D::box2D::vertices() const
{
    const glm::f32vec2& _min = locale_min(),
                        _max = locale_max();

    std::vector<glm::f32vec2> _vertices = {
        _min, {_min.x, _max.y}, {_max.x, _min.y}, _max
    };

    if (m_rigid_body.rotation() != 0.0f)
    {
        for (glm::f32vec2& vert : _vertices)
        {
            math::vec::rotate(vert, m_rigid_body.rotation(), m_rigid_body.position());
        }
    }

    return _vertices;
}

const glm::f32vec2& physics2D::box2D::half_size() const
{
    return m_half_size;
}

glm::f32vec2 physics2D::box2D::locale_min() const
{
    return m_rigid_body.position() - m_half_size;
}

glm::f32vec2 physics2D::box2D::locale_max() const
{
    return m_rigid_body.position() + m_half_size;
}

physics2D::rigid_body2D& physics2D::box2D::rigid_body()
{
    return this->m_rigid_body;
}

const physics2D::rigid_body2D& physics2D::box2D::rigid_body() const
{
    return this->m_rigid_body;
}



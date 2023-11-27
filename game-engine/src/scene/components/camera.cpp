#include "pch.h"
#include "camera.h"


component::camera* component::camera::s_current_camera = nullptr;

component::camera::camera(float left, float right, float bottom, float top) 
    : m_projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
      m_left(left),
      m_right(right),
      m_bottom(bottom),
      m_top(top)
{
}

void component::camera::unselect_camera()
{
    s_current_camera = nullptr;
}

float component::camera::left() const
{
    return m_left;
}

float component::camera::right() const
{
    return m_right;
}
float component::camera::bottom() const
{
    return m_bottom;
}
float component::camera::top() const
{
    return m_top;
}

void component::camera::select_camera()
{
    s_current_camera = this;
}

const glm::f32mat4& component::camera::projection() const
{
    return m_projection;
}

void component::camera::set_projection(float left, float right, float bottom, float top)
{
    m_projection = glm::mat4(glm::ortho(left, right, bottom, top, -1.0f, 1.0f));
    m_left = left;
    m_right = right;
    m_bottom = bottom;
    m_top = top;
}

bool component::camera::is_selected() const
{
    return s_current_camera == this;
}
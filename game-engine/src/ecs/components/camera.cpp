#include "pch.h"
#include "camera.h"


component::camera* component::camera::s_current_camera = nullptr;

component::camera::camera(float left, float right, float bottom, float top) 
    : m_projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
{
}

void component::camera::unselect_camera()
{
    s_current_camera = nullptr;
}

void component::camera::select_camera()
{
    s_current_camera = this;
}

const glm::f32mat4& component::camera::projection() const
{
    return m_projection;
}

bool component::camera::is_selected() const
{
    return s_current_camera == this;
}
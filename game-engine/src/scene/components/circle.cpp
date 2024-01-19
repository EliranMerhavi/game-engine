#include "pch.h"
#include "circle.h"


component::circle::circle(const glm::f32vec4& color) : m_color(color)
{
}

component::circle::circle(float r, float g, float b, float a) 
    : m_color(r, g, b, a)
{
}


const glm::f32vec4& component::circle::color() const
{
    return m_color;
}



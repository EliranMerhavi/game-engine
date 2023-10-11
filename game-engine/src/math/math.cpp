#include "pch.h"
#include "math.h"


void math::vec::rotate(glm::f32vec2& vec, float angle, const glm::f32vec2& origin)
{
    float x = vec.x - origin.x;
    float y = vec.y - origin.y;

    float _cos = std::cos(to_radians(angle));
    float _sin = std::sin(to_radians(angle));

    vec.x = origin.x + (x * _cos) - (y * _sin);
    vec.y = origin.y + (x * _sin) + (y * _cos);
}

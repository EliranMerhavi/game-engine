#include "pch.h"
#include "ray2D.h"

physics2D::ray2D::ray2D(const glm::f32vec2& origin, const glm::f32vec2& direction) : 
	_origin(origin), _direction(glm::normalize(direction))
{
}

#include "pch.h"
#include "raycast_result.h"

physics2D::raycast_result::raycast_result() 
	: _point{0.0f, 0.0f}, 
	  _normal{0.0f, 0.0f},
	  _t(-1),
	  _hit(false)
{
}

void physics2D::raycast_result::init(const glm::f32vec2& point, const glm::f32vec2& normal, float t, bool hit)
{
	this->_point = point;
	this->_normal = normal;
	this->_t = t;
	this->_hit = hit;
}

void physics2D::raycast_result::reset(raycast_result& result)
{
	result._point = result._normal = { 0, 0 };
	result._t = -1;
	result._hit = false;
}
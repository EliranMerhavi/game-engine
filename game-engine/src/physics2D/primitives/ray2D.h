#pragma once

#include "glm/glm.hpp"

namespace physics2D
{
	class ray2D
	{
	public:
		ray2D(const glm::f32vec2& origin, const glm::f32vec2& direction);

		inline glm::f32vec2 origin() const { return this->_origin; }
		inline glm::f32vec2 direction() const { return this->_direction; }

	private:
		glm::f32vec2 _origin;
		glm::f32vec2 _direction;
	};
}
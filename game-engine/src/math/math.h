#pragma once

namespace math
{
	inline float to_radians(float angle)
	{
		return angle * M_PI / 180.0f;
	}

	namespace vec
	{
		void rotate(glm::f32vec2& vec, float angle, const glm::f32vec2& origin);
	}
}
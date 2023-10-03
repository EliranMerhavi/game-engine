#pragma once

namespace math
{
	inline float to_radians(float angle)
	{
		return angle * M_PI / 180.0f;
	}

	inline bool cmp(float x, float y, float epsilon = std::numeric_limits<float>::min())
	{
		return abs(x - y) <= epsilon * std::max(1.0f, std::max(abs(x), abs(y)));
	}

	namespace vec
	{
		void rotate(glm::f32vec2& vec, float angle, const glm::f32vec2& origin);
		
		inline bool cmp(const glm::f32vec2& v1, const glm::f32vec2& v2, float epsilon = std::numeric_limits<float>::min())
		{
			return math::cmp(v1.x, v2.x, epsilon) && math::cmp(v1.y, v2.y, epsilon);
		}
	}
}
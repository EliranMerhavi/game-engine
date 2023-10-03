#pragma once

#include "glm/glm.hpp"

namespace physics2D
{
	class raycast_result
	{
	public:
		raycast_result();

		void init(const glm::f32vec2& point, const glm::f32vec2& normal, float t, bool hit);
		static void reset(raycast_result& result);
	private:
		glm::f32vec2 _point;
		glm::f32vec2 _normal;
		float _t;
		bool _hit;
	};
}
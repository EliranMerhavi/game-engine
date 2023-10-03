#pragma once

#include "../rigid_body/rigid_body2D.h"

namespace physics2D
{
	// AABB - Axis Aligned Bounding Box
	class AABB
	{
	public:
		AABB();
		AABB(const glm::f32vec2& min, const glm::f32vec2& max);

		glm::f32vec2 min() const;
		glm::f32vec2 max() const;
		rigid_body2D& rigid_body();
		const rigid_body2D& rigid_body() const;
	private:
		rigid_body2D m_rigid_body;
		glm::f32vec2 m_size = {};
		glm::f32vec2 m_half_size = {};
	};
}

#pragma once

#include "glm/glm.hpp"
#include <vector>

namespace physics2D
{
	class collision_manifold
	{
	public:
		collision_manifold();
		collision_manifold(const glm::f32vec2& normal, float depth);

		void add_contact_point(const glm::f32vec2& contact);
		const glm::f32vec2& normal() const;
		const std::vector<glm::f32vec2>& contact_points() const;
		float depth() const;
		bool is_colliding() const;
	private:
		glm::f32vec2 m_normal;
		std::vector<glm::f32vec2> m_contact_points;
		float m_depth;
		bool m_is_colliding;
	};
}
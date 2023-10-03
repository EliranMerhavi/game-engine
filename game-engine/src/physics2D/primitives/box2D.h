#pragma once

#include "glm/glm.hpp"
#include "../rigid_body/rigid_body2D.h"
#include <vector>

namespace physics2D
{
	class box2D
	{
	public:
		box2D();
		box2D(const glm::f32vec2& min, const glm::f32vec2& max);

		std::vector<glm::f32vec2> vertices() const;
		const glm::f32vec2& half_size() const;
		glm::f32vec2 locale_min() const;
		glm::f32vec2 locale_max() const;
		
		rigid_body2D& rigid_body();
		const rigid_body2D& rigid_body() const;
	private:
		rigid_body2D m_rigid_body;
		glm::f32vec2 m_size = {};
		glm::f32vec2 m_half_size = {};
	};
}
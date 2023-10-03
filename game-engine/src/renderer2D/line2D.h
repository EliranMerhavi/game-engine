#pragma once


#include "glm/gtc/type_precision.hpp"

namespace renderer2D
{
	class line2D
	{
	public:
		line2D(const glm::f32vec2& from, const glm::f32vec2& to, glm::vec4 color={}, int lifetime=0);
		
		int begin_frame();

		glm::f32vec2 from() const;
		glm::f32vec2 start() const;
		glm::f32vec2 to() const;
		glm::f32vec2 end() const;
		glm::f32vec4 color() const;
		float length2() const;

	private:
		glm::f32vec2 m_from;
		glm::f32vec2 m_to;
		glm::f32vec4 m_color;
		int m_lifetime;
	};
}
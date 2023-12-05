#pragma once
#include "glm/glm.hpp"

namespace component
{
	class circle
	{
	public:
		circle(const glm::f32vec4& color=glm::f32vec4(1.0f));

		const glm::f32vec4& color() const;
	private:
		glm::f32vec4 m_color;
	};
}
#pragma once
#include "glm/glm.hpp"

namespace component
{
	class circle
	{
	public:
		circle(const glm::f32vec4& color=glm::f32vec4(1.0f));
		circle(float r, float g, float b, float a);

		const glm::f32vec4& color() const;
	private:
		glm::f32vec4 m_color;
	};
}
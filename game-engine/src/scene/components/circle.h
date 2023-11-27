#pragma once
#include "glm/glm.hpp"

namespace component
{
	class circle
	{
	public:
		circle();
		circle(const glm::f32vec4& color);

		void set_color(const glm::f32vec4& color);
		const glm::f32vec4& color() const;
	private:
		glm::f32vec4 m_color;
	};
}
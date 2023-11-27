#pragma once
#include "glm/glm.hpp"

namespace component
{
	class quad
	{
	public:
		quad();
		quad(const component::quad& other) = default;
		quad(const glm::f32vec4& color);

		void set_color(const glm::f32vec4& color);
		const glm::f32vec4& color() const;
	private:
		glm::f32vec4 m_color;
	};
}

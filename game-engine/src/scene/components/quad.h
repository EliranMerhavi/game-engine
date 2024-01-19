#pragma once
#include "glm/glm.hpp"
#include <array>
#include "renderer2D/renderer2D.h"

namespace component
{
	class quad
	{
	public:
		quad(float r, float g, float b, float a, const renderer2D::texture_t* texture = &renderer2D::white_texture());
		quad(const glm::f32vec4& color=glm::f32vec4(1), const renderer2D::texture_t* texture = &renderer2D::white_texture());
		quad(const renderer2D::texture_t* texture);

		const renderer2D::texture_t& texture() const;
		const glm::f32vec4& color() const;
	private:
		renderer2D::texture_t const* m_texture;
		glm::f32vec4 m_color;
	};
}

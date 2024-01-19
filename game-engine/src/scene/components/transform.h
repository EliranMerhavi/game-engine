#pragma once
#include "glm/glm.hpp"
#include <tuple>

namespace component
{
	class transform
	{
	public:

		transform();
		transform(const glm::f32vec2& position, const glm::f32vec2& scale, float rotation);

		void set_data(const glm::f32vec2& position, const glm::f32vec2& scale, float rotation=0.0f);
		std::tuple<glm::f32vec2, glm::f32vec2, float> data() const;

		void set_position(const glm::f32vec2& position);
		void set_scale(const glm::f32vec2& scale);
		void set_rotation(float rotation);

		const glm::f32vec2& position() const { return m_position; }
		const glm::f32vec2& scale() const { return m_scale; }
		float rotation() const { return m_rotation; }

		const glm::f32mat4& matrix() const;
	private:
		void update_cache();

		glm::f32mat4 m_cache;
		glm::f32vec2 m_position;
		glm::f32vec2 m_scale;
		float m_rotation;
	};
}
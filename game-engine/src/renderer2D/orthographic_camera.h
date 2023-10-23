#pragma once

#include <glm/glm.hpp>

namespace game_engine
{
	class orthographic_camera
	{
	public:
		orthographic_camera(float left, float right, float bottom, float top);

		const glm::f32vec2& position() const;
		void set_position(const glm::f32vec3& position);
		
		float rotation() const;
		void set_rotation(float rotation);

		const glm::f32mat4& projection() const { return m_projection; }
		const glm::f32mat4& view() const { return m_view; }
		const glm::f32mat4& view_projection() const { return m_cache; }

		void update();
	private:
		glm::f32mat4 m_projection, m_view, m_cache;

		glm::f32vec3 m_position;
		float m_rotation;
	};
}
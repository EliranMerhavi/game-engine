#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace component
{
	class camera
	{
	public:
		camera() = default;
		camera(float left, float right, float bottom, float top);
		static void unselect_camera();
		void select_camera();
		bool is_selected() const;
		const glm::f32mat4& projection() const;
		
		void set_projection(float left, float right, float bottom, float top);

		float left() const;
		float right() const;
		float bottom() const;
		float top() const;
	private:
		static component::camera* s_current_camera;
		glm::f32mat4 m_projection;
		float m_left, 
			m_right, 
			m_bottom, 
			m_top;
	};
}

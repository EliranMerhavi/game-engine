#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace component
{
	class camera
	{
	public:
		camera(float left, float right, float bottom, float top);
		static void unselect_camera();
		void select_camera();
		bool is_selected() const;
		const glm::f32mat4& projection() const;
	private:
		static component::camera* s_current_camera;
		glm::f32mat4 m_projection;
	};
}

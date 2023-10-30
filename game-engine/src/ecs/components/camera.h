#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace component
{
	class camera
	{
	public:
		camera(float left, float right, float bottom, float top);
		void select_camera();
		const glm::f32mat4& projection() const;
		static component::camera* current_camera();
	private:
		static component::camera* s_current_camera;
		glm::f32mat4 m_projection;
	};
}

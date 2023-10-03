#pragma once

#include "glm/glm.hpp"

namespace physics2D
{
	enum class collider_type {
		CIRCLE
	};
	class collider2D
	{
	public:
		collider2D(collider_type type);
		
		//TODO: implement this
		virtual float get_inertia_tensor(float mass) = 0;
		collider_type type() const;
	private:
		collider_type m_type;
	protected:
		glm::f32vec2 m_offset;
	};
}

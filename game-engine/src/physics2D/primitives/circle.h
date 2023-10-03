#pragma once

#include "../rigid_body/rigid_body2D.h"

namespace physics2D
{
	class circle : public collider2D
	{
	public:
		circle();
		const glm::f32vec2& center() const;
		float& radius();
		float radius() const;
		rigid_body2D& rigid_body();
		const rigid_body2D& rigid_body() const;
		virtual float get_inertia_tensor(float mass) override;
	private:
		float m_radius;
		rigid_body2D m_rigid_body;
	};
}

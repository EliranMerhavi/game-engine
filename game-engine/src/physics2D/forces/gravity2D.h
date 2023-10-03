#pragma once
#include "forces.h"
#include "glm/glm.hpp"

namespace physics2D
{
	namespace forces
	{
		class gravity2D : public force_generator
		{
		public:
			gravity2D(const glm::f32vec2& force);
			virtual void generate_force(rigid_body2D& rigid_body, float delta_time) override;

		private:
			glm::f32vec2 m_gravity;
		};
	}
}
#pragma once
#include "forces/forces.h"
#include "forces/gravity2D.h"
#include "rigid_body/collision_manifold.h"
#include <list>

namespace physics2D
{
	class physics_system2D
	{
	public:
		physics_system2D(float fixed_update_dt, const glm::f32vec2& gravity);

		void update(float dt);
		void fixed_update();
		void add_rigid_body(const rigid_body2D& rigid_body, bool add_gravity);
		
	private:
		
		void apply_impulse(rigid_body2D& a, rigid_body2D& b, collision_manifold m);

		forces::force_registry m_force_registry;
		forces::gravity2D m_gravity;

		std::vector<rigid_body2D> m_rigid_bodies;
		std::vector<rigid_body2D> m_bodies1;
		std::vector<rigid_body2D> m_bodies2;
		std::vector<collision_manifold> m_collisions;

		float m_fixed_update;
		static const int s_impulse_iterations = 6;
	};
}
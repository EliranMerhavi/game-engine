#pragma once

#include "../primitives/collider2D.h"

namespace physics2D
{
	
	class rigid_body2D
	{
	#define INFINITE_MASS 0.0f
	public:
		rigid_body2D();

		void physics_update(float dt);
		void clear_accumulators();
		void add_force(const glm::f32vec2& force);

		void set_transform(const glm::f32vec2& position, float rotation);
		void set_transform(const glm::f32vec2& position);
		float& cor();
		glm::f32vec2& velocity();
		collider2D* collider();

		const collider2D* collider() const;
		const glm::f32vec2& position() const;
		float rotation() const;
		float mass() const;
		float inverse_mass() const;
		float cor() const;
		const glm::f32vec2& velocity() const;

		bool has_infinite_mass() const;
		bool operator==(const rigid_body2D& other) const;
	private:
		collider2D* m_collider;
		glm::f32vec2 m_position;
		float m_rotation;
		float m_mass;
		float m_inverse_mass;

		glm::f32vec2 m_force_accum;
		glm::f32vec2 m_linear_velocity;
		float m_angular_velocity;
		float m_linear_damping;
		float m_angular_damping;
		
		// Coefficient of restitution
		float m_cor;

		bool m_fixed_rotation;
		
		size_t m_id;
		static size_t s_rigid_body_ID;
	};
}
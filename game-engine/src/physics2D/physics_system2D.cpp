#include "pch.h"
#include "physics_system2D.h"
#include "rigid_body/collisions.h"

physics2D::physics_system2D::physics_system2D(float fixed_update_dt, const glm::f32vec2& gravity)
	:
	m_force_registry(),
	m_gravity(gravity),
	m_rigid_bodies(),
	m_bodies1(),
	m_bodies2(),
	m_collisions(),
	m_fixed_update(fixed_update_dt)
{
}

void physics2D::physics_system2D::update(float dt)
{
	fixed_update();
}

void physics2D::physics_system2D::fixed_update()
{
	m_bodies1.clear();
	m_bodies2.clear();
	m_collisions.clear();
	// find any collisions
	// TODO: optimize this part 
	// IDEA: learn about quad tree
	size_t size = m_rigid_bodies.size();
	
	std::vector<bool> rigid_bodies_to_skip(size, false);

	for (size_t i = 0; i < size; i++)
	{
		rigid_body2D r1 = m_rigid_bodies[i];
		collider2D* c1 = r1.collider();
		
		if (!c1 || r1.has_infinite_mass())
			continue;

		for (size_t j = i + 1; j < size; j++)
		{
			if (rigid_bodies_to_skip[j])
				continue;
			collision_manifold result;
			
			rigid_body2D r2 = m_rigid_bodies[j];
			collider2D* c2 = r2.collider();

			if (!c2 || r2.has_infinite_mass())
			{
				rigid_bodies_to_skip[j] = true;
				continue;
			}

			result = collisions::find_collision_features(*c1, *c2);
			if (result.is_colliding())
			{
				m_bodies1.emplace_back(r1);
				m_bodies2.emplace_back(r2);
				m_collisions.emplace_back(result);
			}
		}
	}
	// update the forces
	m_force_registry.update_forces(m_fixed_update);

	// resolve collisions via iterative impulse resolution
	// iterate a certain amount of times to get an approximate solution
	for (size_t i = 0; i < s_impulse_iterations; i++)
	{
		for (size_t i = 0; i < m_collisions.size(); i++)
		{
			size_t j_size = m_collisions[i].contact_points().size();
			for (size_t j = 0; j < j_size; j++)
			{
				rigid_body2D r1 = m_bodies1[i];
				rigid_body2D r2 = m_bodies2[i];
				apply_impulse(r1, r2, m_collisions[i]);
			}
		}
	}
	// update the velocities of all rigid bodies
	for (auto& rigid_body : m_rigid_bodies)
		rigid_body.physics_update(m_fixed_update);
}

void physics2D::physics_system2D::add_rigid_body(const rigid_body2D& rigid_body, bool add_gravity)
{
	m_rigid_bodies.emplace_back(rigid_body);
	if (add_gravity)
		m_force_registry.add(m_rigid_bodies.back(), m_gravity);
}

void physics2D::physics_system2D::apply_impulse(rigid_body2D& a, rigid_body2D& b, collision_manifold m)
{
	// linear velocity
	float inv_mass1 = a.inverse_mass();
	float inv_mass2 = b.inverse_mass();
	float inv_mass_sum = inv_mass1 + inv_mass2;
	if (inv_mass_sum == 0.0f)
		return;
	
	// relative velocity
	glm::f32vec2 relative_vel = b.velocity() - a.velocity();
	glm::f32vec2 relative_normal = glm::normalize(m.normal());
	// moving away from each other? do nothing
	if (glm::dot(relative_normal, relative_normal) > 0.0f)
		return;
	
	float e = std::min(a.cor(), b.cor());
	float numerator = -(1.0f + e) * glm::dot(relative_vel, relative_normal);
	float j = numerator / inv_mass_sum;
	if (m.contact_points().size() > 0 && j != 0.0f)
		j /= (float)m.contact_points().size();
	
	glm::f32vec2 impulse = relative_normal * j;

	a.velocity() = a.velocity() + impulse * inv_mass1 * -1.0f;
	b.velocity() = b.velocity() + impulse * inv_mass2;
}
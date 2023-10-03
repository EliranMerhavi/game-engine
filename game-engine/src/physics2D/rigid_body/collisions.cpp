#include "pch.h"
#include "collisions.h"


physics2D::collision_manifold physics2D::collisions::find_collision_features(const collider2D& c1, const collider2D& c2)
{
	if (c1.type() == collider_type::CIRCLE && c2.type() == collider_type::CIRCLE)
	{
		return find_collision_features(*static_cast<const circle*>(&c1), *static_cast<const circle*>(&c2));
	}

	throw std::exception("unknown collider");
}


physics2D::collision_manifold physics2D::collisions::find_collision_features(const circle& a, const circle& b)
{
	collision_manifold result;
	float sum_radii = a.radius() + b.radius();
	glm::f32vec2 distance = b.center() - a.center();
	if (glm::length2(distance) - (sum_radii * sum_radii) > 0)
		return result;
	// multiply by 0.5 because we want to separate each circle the
	// amount. consider updating to factor in the momenum and velocity
	float depth = abs(distance.length() - sum_radii) * 0.5f;
	glm::f32vec2 normal = glm::normalize(distance);
	float distance_to_point = a.radius() - depth;
	glm::f32vec2 contact_point = a.center() + normal * distance_to_point;
	
	result = collision_manifold(normal, depth);
	result.add_contact_point(contact_point);
	return result;
}

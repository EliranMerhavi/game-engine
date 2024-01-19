#include "pch.h"
#include "phsyics.h"
#include "scene/components.h"
#include "scene/scene_t.h"
#include "circCollisions.h"

phsyics2D_system::phsyics2D_system(scene_t& _scene) : m_scene(_scene)
{
}

void phsyics2D_system::update()
{
	const auto& entities = m_scene.m_registry.entities<component::rigidBody>();
	int n = entities.size();


	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			game_object_t obj1(entities[i], m_scene),
						  obj2(entities[j], m_scene);
			
			collisions::type type1 = obj1.get<component::rigidBody>().collision_type,
							 type2 = obj2.get<component::rigidBody>().collision_type,
							 collision_type;

			if (type1 == collisions::type::IGNORED || type2 == collisions::type::IGNORED) {
				collision_type = collisions::type::IGNORED;
			}
			else if (type1 == collisions::type::LINEAR || type2 == collisions::type::LINEAR) {
				collision_type = collisions::type::LINEAR;
			}
			else {
				collision_type = collisions::type::ROTATIONAL;
			}


			if (obj1.has<component::circle>() && obj2.has<component::circle>()) {

				switch (collision_type)
				{
				case collisions::type::IGNORED:
					if (circCollisions::isColliding(obj2, obj1)) {
						if (obj1.has<component::collider_callback>()) {
							obj1.get<component::collider_callback>()(obj1, obj2);
						}
						if (obj2.has<component::collider_callback>()) {
							obj2.get<component::collider_callback>()(obj2, obj1);
						}
					}
					break;
				case collisions::type::LINEAR:
					circCollisions::linearCollision(obj2, obj1, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
					break;
				case collisions::type::ROTATIONAL:
					circCollisions::rotationalCollision(obj2, obj1, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
					break;
				}
			}
			if (obj1.has<component::circle>() && obj2.has<component::quad>()) {
				switch (collision_type)
				{
				case collisions::type::IGNORED:
					if (rectCircCollisions::isColliding(obj2, obj1)) {
						if (obj1.has<component::collider_callback>()) {
							obj1.get<component::collider_callback>()(obj1, obj2);
						}
						if (obj2.has<component::collider_callback>()) {
							obj2.get<component::collider_callback>()(obj2, obj1);
						}
					}
					break;
				case collisions::type::LINEAR:
					rectCircCollisions::linearCollision(obj2, obj1, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
					break;
				case collisions::type::ROTATIONAL:
					rectCircCollisions::rotationalCollision(obj2, obj1, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
					break;
				}
			}
			if (obj2.has<component::circle>() && obj1.has<component::quad>()) {
				switch (collision_type)
				{
				case collisions::type::IGNORED:
					if (rectCircCollisions::isColliding(obj1, obj2)) {
						if (obj1.has<component::collider_callback>()) {
							obj1.get<component::collider_callback>()(obj1, obj2);
						}
						if (obj2.has<component::collider_callback>()) {
							obj2.get<component::collider_callback>()(obj2, obj1);
						}
					}
					break;
				case collisions::type::LINEAR:
					rectCircCollisions::linearCollision(obj1, obj2, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
					break;
				case collisions::type::ROTATIONAL:
					rectCircCollisions::rotationalCollision(obj1, obj2, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
					break;
				}
			}
			if (obj1.has<component::quad>() && obj2.has<component::quad>()) {
				switch (collision_type)
				{
				case collisions::type::IGNORED:
					if (rectCollisions::isColliding(obj2, obj1)) {
						if (obj1.has<component::collider_callback>()) {
							obj1.get<component::collider_callback>()(obj1, obj2);
						}
						if (obj2.has<component::collider_callback>()) {
							obj2.get<component::collider_callback>()(obj2, obj1);
						}
					}
					break;
				case collisions::type::LINEAR:
					rectCollisions::linearCollision(obj1, obj2, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
					break;
				case collisions::type::ROTATIONAL:
					rectCollisions::rotationalCollision(obj1, obj2, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
					break;
				}
			}
		}
	}

	for (auto entity : entities) {
		auto& transform = m_scene.m_registry.get<component::transform>(entity);
		auto& rigid_body = m_scene.m_registry.get<component::rigidBody>(entity);
		
		rigid_body.velocity += rigid_body.acceleration;

		transform.set_position(transform.position() + rigid_body.velocity);
		transform.set_rotation(transform.rotation() + rigid_body.omega * 180/M_PI);
	}
}

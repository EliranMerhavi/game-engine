#include "pch.h"
#include "phsyics.h"
#include "scene/components.h"
#include "scene/scene_t.h"
#include "circCollisions.h"
#include "rectCircCollisions.h"
#include "rectCollisions.h"

phsyics2D_system::phsyics2D_system(scene_t& _scene) : m_scene(_scene)
{
}

void phsyics2D_system::update()
{
	const auto& entities = m_scene.m_registry.pool<component::rigidBody>().entities();
	int n = entities.size();


	for (int i = 0; i < n; i++) {

		for (int j = i + 1; j < n; j++) {
			game_object_t obj1(entities[i], m_scene),
						  obj2(entities[j], m_scene);

			if (obj1.has<component::circle>() && obj2.has<component::circle>())
				circCollisions::rotationalCollision(obj1, obj2, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
			if (obj1.has<component::circle>() && obj2.has<component::quad>()) 
				rectCircCollisions::rotationalCollision(obj2, obj1, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
			if (obj2.has<component::circle>() && obj1.has<component::quad>())
				rectCircCollisions::rotationalCollision(obj1, obj2, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
			if (obj1.has<component::quad>() && obj2.has<component::quad>())
				rectCollisions::rotationalCollision(obj1, obj2, std::min(obj1.get<component::rigidBody>().restitution, obj2.get<component::rigidBody>().restitution));
				
				//std::cout << obj2.get<component::rigidBody>().velocity.y << ", " << obj2.get<component::rigidBody>().omega << "\n";
		}
	}

	for (auto entity : entities) {
		auto& transform = m_scene.m_registry.get<component::transform>(entity);
		auto& rigid_body = m_scene.m_registry.get<component::rigidBody>(entity);
		if (!rigid_body.staticPos) {
			rigid_body.acceleration = { 0,-0.2 };
		}
		
		rigid_body.velocity += rigid_body.acceleration;
		transform.set_position(transform.position() + rigid_body.velocity);
		transform.set_rotation(transform.rotation() + rigid_body.omega * 180/M_PI);
	}
}

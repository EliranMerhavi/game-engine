#include "pch.h"
#include "phsyics.h"
#include "scene/components.h"
#include "scene/scene.h"
#include "circCollisions.h"

phsyics2D_system::phsyics2D_system(game_engine::scene& _scene) : m_scene(_scene)
{
}

void phsyics2D_system::update()
{
	const auto& entities = m_scene.m_registry.pool<component::rigidBody>().entities();
	int n = entities.size();

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			game_engine::game_object obj1(entities[i], m_scene),
									 obj2(entities[j], m_scene);
			if (obj1.has<component::circle>() && obj2.has<component::circle>())
				circCollisions::linearCollision(obj1, obj2, 1);
		}
	}

	for (auto entity : entities) {
		auto& transform = m_scene.m_registry.get<component::transform>(entity);
		auto& rigid_body = m_scene.m_registry.get<component::rigidBody>(entity);

		transform.set_position(transform.position() + rigid_body.velocity);
	}
}

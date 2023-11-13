#include "pch.h"
#include "phsyics.h"
#include "ecs/components.h"
#include "circCollisions.h"

phsyics2D_system::phsyics2D_system(ecs::registry& registry) : registry(registry)
{
}

void phsyics2D_system::update()
{
	const auto& entities = registry.pool<component::rigidBody>().entities();
	int n = entities.size();

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			game_engine::game_object obj1(entities[i], registry), 
									 obj2(entities[j], registry);
			if (obj1.has<component::circle>() && obj2.has<component::circle>())
				circCollisions::linearCollision(obj1, obj2, 1);
		}
	}

	for (auto entity : entities) {
		auto& transform = registry.get<component::transform>(entity);
		auto& rigid_body = registry.get<component::rigidBody>(entity);

		transform.set_position(transform.position() + rigid_body.velocity);
	}
}

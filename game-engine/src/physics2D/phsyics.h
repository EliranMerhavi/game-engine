#pragma once

#include "ecs/registry.h"


class phsyics2D_system {
public:
	phsyics2D_system(ecs::registry& registry);
	void update();

private:
	ecs::registry& registry;
};

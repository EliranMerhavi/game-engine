#pragma once

#include "ecs/registry.h"


class scene_t;

class phsyics2D_system {
public:
	phsyics2D_system(scene_t& _scene);
	void update();

private:
	scene_t& m_scene;
};

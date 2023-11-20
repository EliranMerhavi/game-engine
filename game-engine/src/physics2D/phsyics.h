#pragma once

#include "ecs/registry.h"

namespace game_engine 
{
	class scene;
}

class phsyics2D_system {
public:
	phsyics2D_system(game_engine::scene& _scene);
	void update();

private:
	game_engine::scene& m_scene;
};

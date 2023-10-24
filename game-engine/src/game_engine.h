#pragma once

#include "core/config.h"
#include "scene/scene.h"

namespace game_engine
{
	void run(const config_t& config={});
	void set_scene(scene& scene);

	namespace config
	{
		void set_vsync(bool vsync);
		void set_limitFPS(float fps);
	}
}
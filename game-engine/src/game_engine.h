#pragma once

#include "core/config.h"

namespace game_engine
{
	class scene;

	void init(const config_t& config={});
	void run();
	void set_scene(scene& scene);

	namespace config
	{
		void set_vsync(bool vsync);
		void set_limitFPS(float fps);
	}
}
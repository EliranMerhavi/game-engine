#pragma once

#include "core/config.h"

struct GLFWwindow;

namespace game_engine
{
	class scene;

	void init(const config_t& config={});
	void run();
	void set_scene(scene& scene);
	GLFWwindow* window();

	namespace config
	{
		int window_width();
		int window_height();
		void set_vsync(bool vsync);
		void set_limitFPS(float fps);
		const config_t& get_config();		
	}
}
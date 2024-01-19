#pragma once

#include "core/config.h"

struct GLFWwindow;
class scene_t;

namespace game_engine
{
	void init(const config_t& config={});
	void run();
	void set_scene(scene_t& scene);
	GLFWwindow* window();

	namespace config
	{
		int window_width();
		int window_height();
		void set_vsync(bool vsync);
		const config_t& get_config();		
	}
}
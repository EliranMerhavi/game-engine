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
		const std::pair<uint32_t, uint32_t>& window_size();
		void set_vsync(bool vsync);
		const config_t& get_config();		
	}
}
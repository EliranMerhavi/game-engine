#pragma once

#include <string>

namespace game_engine
{
	struct scene;
}


#define UNLIMITED_FPS 0.0f

struct config_t
{
	bool vsync = false;
	float limitFPS = 0.0f;

	std::string window_title = "default";
	int starting_width = 500;
	int starting_height = 500;
	game_engine::scene* starting_scene = nullptr;
};
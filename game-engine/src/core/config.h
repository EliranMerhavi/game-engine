#pragma once

#include <string>


struct scene_t;

#define UNLIMITED_FPS 0.000001f

struct config_t
{
	bool vsync = false;
	std::string window_title = "default";
	std::pair<uint32_t, uint32_t> window_size = { 500, 500 };
	scene_t* starting_scene = nullptr;
};
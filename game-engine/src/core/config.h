#pragma once

#include <string>


struct scene_t;

#define UNLIMITED_FPS 0.000001f

struct config_t
{
	bool vsync = false;

	std::string window_title = "default";
	int width = 500;
	int height = 500;
	scene_t* starting_scene = nullptr;
};
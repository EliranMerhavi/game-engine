#pragma once

#include <string>

struct config_t
{
	bool vsync = false;
	float limitFPS = 0.0f;

	std::string window_title = "default";
	int starting_width = 500;
	int starting_height = 500;
};
#define GLEW_STATIC
#include "game_engine.h"
#include "scenes/test_scene.h"
#include <iostream>


int main(int argc, const char** argv)
{
	srand(time(nullptr));
	
	test_scene test;
	config_t config;

	config.limitFPS = 1.0f / 60.0f;
	config.vsync = true;

	game_engine::set_scene(test);
	game_engine::run(config);

	return 0;
}
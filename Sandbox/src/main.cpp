#define GLEW_STATIC
#include "game_engine.h"
#include "scenes/test_scene.h"
#include <iostream>


int main(int argc, const char** argv)
{
	srand(time(nullptr));
	
	config_t config;

	config.limitFPS = 1.0f / 60.0f;
	config.vsync = false;
	config.starting_scene = new test_scene();

	game_engine::init(config);
	game_engine::run();
	delete config.starting_scene;
	return 0;
}
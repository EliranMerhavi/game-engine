#include "game_engine.h"
#include "scenes/performance_test.h"
#include "scenes/test_scene.h"
#include <iostream>

int main(int argc, const char** argv)
{
	// srand(time(nullptr));

	config_t config;

	config.vsync = false;
	config.starting_scene = new performance_test();
	config.window_size = { 1000, 500 };

	game_engine::init(config);
	game_engine::run();
	delete config.starting_scene;
	return 0;
}
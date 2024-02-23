#define GLEW_STATIC
#include "game_engine.h"
#include "levels/level0.h"
#include "scenes/performance_test.h"
#include "scenes/test_scene.h"


int main(int argc, const char** argv)
{
	// srand(time(nullptr));

	config_t config;

	config.vsync = false;
	config.starting_scene = new performance_test();

	config.height = 500;
	config.width = 1000;

	game_engine::init(config);
	game_engine::run();
	delete config.starting_scene;
	return 0;
}
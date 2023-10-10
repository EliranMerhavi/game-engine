#define GLEW_STATIC
#include "game_engine.h"
#include "scenes/test_scene.h"
#include <iostream>

int main(int argc, const char** argv)
{
	srand(time(nullptr));
	game_engine::application& application{ game_engine::application::instance() };
	test_scene test;
	
	application.set_current_scene(test);
	application.run();


	return 0;
}
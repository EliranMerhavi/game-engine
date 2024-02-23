#include "level0.h"

void level0(test_scene& scene)
{
	int width = game_engine::config::window_width(), height = game_engine::config::window_height();

	scene.create_ball({ 200, height / 2 });
	scene.create_goal({ width - 100, height / 2 }, { 20 , 20 });

	scene.create_obstacle(obstacle_t::RECT, { 20, 20 }, { 50 , 50 }, component::rigidBody(collisions::type::ROTATIONAL, 0, 0, { 0, 0 }, true, true));
}
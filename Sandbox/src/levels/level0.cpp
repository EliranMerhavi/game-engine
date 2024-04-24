#include "level0.h"

void level0(test_scene& scene)
{
	const auto& [width, height] = game_engine::config::window_size();

	scene.create_ball({ 200, height / 2 });
	scene.create_goal({ width - 100, height / 2 }, { 20 , 20 });

	scene.create_obstacle(obstacle_t::RECT, { 20, 20 }, { 50 , 50 }, component::rigidBody(collisions::type::ROTATIONAL, 0, 0, { 0, 0 }, true, true));
}
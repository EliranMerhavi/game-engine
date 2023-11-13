#include "test_scene.h"
#include "ecs/components/rigidBody.h"
#include "scene/game_object.h"
#include "ecs/components.h"
#include "renderer2D/renderer2D_utils.h"
#include "core/input.h"


test_scene::test_scene()
{
}

void test_scene::on_create()
{
	game_engine::game_object camera = create_game_object();

	camera.add<component::camera>(-200, 200, -200, 200);
	camera.get<component::camera>().select_camera();

	game_engine::game_object obj1 = create_game_object();

	obj1.get<component::transform>().set_transform({ 0, 0 }, {50, 50});
	obj1.add<component::rigidBody>();
	obj1.get<component::rigidBody>().intialize(10, 10, {0.25, 0}, "circle");
	obj1.add<component::circle>();

	game_engine::game_object obj2 = create_game_object();

	obj2.get<component::transform>().set_transform({ 100, 0 }, { 50, 50 });
	obj2.add<component::circle>();
	obj2.add<component::rigidBody>();
	obj2.get<component::rigidBody>().intialize(10, 10, { 0, 0 }, "circle");
}

test_scene::~test_scene()
{
}




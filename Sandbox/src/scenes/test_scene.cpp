#include "test_scene.h"
#include "ecs/components/rigidBody.h"
#include "scene/game_object.h"
#include "ecs/components.h"
#include "renderer2D/renderer2D_utils.h"
#include "core/input.h"
#include "physics2D/forces.h"

test_scene::test_scene()
{
}

struct bool_holder {
	bool b = false;
};

void test_scene::on_create()
{
	game_engine::game_object camera = create_game_object();
	
	camera.add<component::camera>(-300, 300, -300, 300);
	camera.get<component::camera>().select_camera();

	game_engine::game_object obj1 = create_game_object();

	obj1.get<component::transform>().set_transform({ 160, 0 }, { 100, 100 });
	obj1.get<component::transform>().set_rotation(0);
	obj1.add<component::circle>();
	obj1.add<component::rigidBody>();
	auto& rigid1 = obj1.get<component::rigidBody>();
	rigid1.intialize(10000, 0, { 0,0 });
	//rigid1.applyForce({ 0,-rigid1.mass / 30 });
	game_engine::game_object obj2 = create_game_object();

	obj2.get<component::transform>().set_transform({-140, 0 }, { 100, 100 });
	obj2.get<component::transform>().set_rotation(0);
	obj2.add<component::circle>();
	obj2.add<component::rigidBody>();
	auto& rigid2 = obj2.get<component::rigidBody>();
	rigid2.intialize(10000, 0, { 0,0 });
	//rigid2.applyForce({ 0,-rigid2.mass / 30 });
	obj2.get<component::rigidBody>().restitution = 1;

	game_engine::game_object obj3 = create_game_object();

	obj3.get<component::transform>().set_transform({ 0, -200 }, { 500, 10 });
	obj3.get<component::transform>().set_rotation(0);
	obj3.add<component::quad>();
	obj3.add<component::rigidBody>();
	obj3.get<component::rigidBody>().intialize(4000, 0, { 0,0 });
	obj3.get<component::rigidBody>().staticPos = 1;
	obj3.get<component::rigidBody>().staticRot = 0;
	obj3.get<component::rigidBody>().restitution = 0.9;
	


}

test_scene::~test_scene()
{
}




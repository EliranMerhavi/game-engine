#include "test_scene.h"
#include "ecs/components/rigidBody.h"
#include "scene/game_object.h"
#include "ecs/components.h"
#include "renderer2D/renderer2D_utils.h"

test_scene::test_scene()
{

}

void test_scene::on_create()
{
	game_engine::game_object camera = create_game_object();

	camera.add<component::camera>(-500.0f, 500.0f, -500.0f, 500.0f);
	camera.get<component::camera>().select_camera();
	auto& camera_transform = camera.get<component::transform>();
	camera_transform.set_scale(camera_transform.scale() - glm::f32vec2{ 0.5, 0.5 });

	//game_engine::game_object obj1 = create_game_object("obj"); 
	
	//obj1.get<component::transform>().set_position({ 250.0f, 250.0f });
	//obj1.get<component::transform>().set_scale({ 250.0f, 250.0f });
	//obj1.add<component::quad>();
	//obj1.add<component::update_callback>([obj1] {
		//auto& transform = obj1.get<component::transform>();
		//transform.set_rotation(fmod(transform.rotation() + time::delta_time(), 360));
	//});	

	

	game_engine::game_object obj2 = create_game_object();
	obj2.add<component::quad>();
	obj2.get<component::quad>().set_color({ 0.0f, 1.0f, 0.0f, 1.0f });
	obj2.get<component::transform>().set_position({ 0,0 });
	obj2.get<component::transform>().set_scale({150,50});
	obj2.get<component::transform>().set_rotation(45);
	obj2.add<component::update_callback>([obj2] {
		auto& transform = obj2.get<component::transform>();
		glm::f32vec2 velocity = { time::delta_time(), -time::delta_time() };
		transform.set_position(transform.position() + velocity);
		});
	obj2.get<component::transform>().rotation();
	
	game_engine::game_object rigidB = create_game_object();
	rigidB.add<component::rigidBody>();
	rigidB.get<component::rigidBody>().intialize(1, 100, { 0,0 }, "box");
	rigidB.get<component::transform>().set_position({ 0,0 });


	game_engine::game_object rigidA = create_game_object();
	rigidA.add<component::rigidBody>();
	rigidA.get<component::rigidBody>().intialize(1, 100, { -1,0 }, "box");
	rigidA.get<component::transform>().set_position({ 100,0 });
	rigidA.add<component::update_callback>([rigidA] {
		auto& transform = rigidA.get<component::transform>();
		auto& object = rigidA.get<component::rigidBody>();
		transform.set_position(transform.position() + object.velocity);
		});
}




test_scene::~test_scene()
{
	renderer2D::free_texture(texture);
}




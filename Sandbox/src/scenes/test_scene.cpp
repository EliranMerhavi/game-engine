#include "test_scene.h"

#include "scene/game_object.h"
#include "ecs/components.h"
#include "renderer2D/renderer2D_utils.h"

test_scene::test_scene()
{

}

void test_scene::on_create()
{
	game_engine::game_object camera = create_game_object();

	camera.add<component::camera>(0.0f, 500.0f, 500.0f, 0.0f);
	camera.get<component::camera>().select_camera();
	auto& camera_transform = camera.get<component::transform>();
	camera_transform.set_scale(camera_transform.scale() - glm::f32vec2{ 0.5, 0.5 });

	game_engine::game_object obj1 = create_game_object("obj"); 
	
	obj1.get<component::transform>().set_position({ 250.0f, 250.0f });
	obj1.get<component::transform>().set_scale({ 250.0f, 250.0f });
	obj1.add<component::quad>();
	obj1.add<component::update_callback>([obj1] {
		auto& transform = obj1.get<component::transform>();
		transform.set_rotation(fmod(transform.rotation() + time::delta_time(), 360));
	});	

	game_engine::game_object obj2 = create_game_object();
	obj2.add<component::circle>();
	obj2.get<component::circle>().set_color({ 1.0f, 0.0f, 0.0f, 1.0f });
	obj2.get<component::transform>().set_position({ 50.0f, 50.0f });
	obj2.get<component::transform>().set_scale({100,100});
}

test_scene::~test_scene()
{
	renderer2D::free_texture(texture);
}




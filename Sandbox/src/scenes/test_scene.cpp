#include "test_scene.h"

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
	auto& camera_transform = camera.get<component::transform>();
	camera_transform.set_scale(camera_transform.scale() - glm::f32vec2{ 0.5, 0.5 });

	game_engine::game_object obj1 = create_game_object("obj"); 
	
	obj1.get<component::transform>().set_transform({ 0, 0 }, { 50.0f, 50.0f });

	obj1.add<component::quad>(glm::f32vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

	obj1.add<component::update_callback>([obj1] {
		auto& transform = obj1.get<component::transform>();
		glm::f32vec2 update{ 0, 0 };

		if (input::get_key_state(key::A) == key_state::PRESSED) {
			update.x -= time::delta_time();
		}
		if (input::get_key_state(key::S) == key_state::PRESSED) {
			update.y -= time::delta_time();
		}
		if (input::get_key_state(key::D) == key_state::PRESSED) {
			update.x += time::delta_time();
		}
		if (input::get_key_state(key::W) == key_state::PRESSED) {
			update.y += time::delta_time();
		}

		transform.set_position(transform.position() + update);
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




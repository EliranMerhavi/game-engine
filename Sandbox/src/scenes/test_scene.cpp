#include "test_scene.h"

#include "ecs/components.h"

#include "scene/game_object.h"
#include "core/input.h"

#include "renderer2D/renderer2D_utils.h"


test_scene::test_scene()
{
}

void test_scene::on_create()
{
	game_engine::game_object camera = create_game_object();
	
	camera.add<component::camera>(250, -250, 250, -250);
	camera.get<component::camera>().select_camera();

	game_engine::game_object obj = create_game_object();

	obj.get<component::transform>().set_transform({ 0, 0  }, { 250, 250 });
	obj.add<component::texture>("assets/images/container.jpg");
	obj.add<component::update_callback>(obj, [](game_engine::game_object& obj) {
		auto& scene = obj.scene();
		auto& transform = obj.get<component::transform>();
		auto new_pos = scene.to_world_position(input::get_mouse_position());

		transform.set_position(new_pos);
	});
}

test_scene::~test_scene()
{
}




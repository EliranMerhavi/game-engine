#include "test_scene.h"
#include "ecs/components/rigidBody.h"
#include "scene/game_object.h"
#include "ecs/components.h"
#include "renderer2D/renderer2D_utils.h"
#include "core/input.h"


test_scene::test_scene()
{
}

struct bool_holder {
	bool b = false;
};

void test_scene::on_create()
{
	game_engine::game_object camera = create_game_object();
	
	camera.add<component::camera>(-200, 200, -200, 200);
	camera.get<component::camera>().select_camera();

	game_engine::game_object obj = create_game_object();

	obj.add<bool_holder>();
	obj.get<component::transform>().set_transform({250, 250}, {50, 50});
	obj.add<component::quad>();
	obj.add<component::update_callback>(obj, [](game_engine::game_object& obj) {
		auto& scene = obj.scene();
		
		auto& transform = obj.get<component::transform>();
		auto& is_floating = obj.get<bool_holder>();
		auto mouse_pos = input::get_mouse_position();
		
		if (is_floating.b) {
			is_floating.b = (input::get_mouse_state(mouse::BUTTON1) != input::state::PRESSED);
			transform.set_position(mouse_pos);
		}
		else { 
			is_floating.b = (input::get_mouse_state(mouse::BUTTON1) == input::state::PRESSED && glm::distance(mouse_pos, transform.position()));
		}
		
		auto offset{ input::get_mouse_scroll_offset() };
		
		float scroll = 0;
		
		scroll +=
			(offset < 0) * (2 * time::delta_time()) -
			(offset > 0) * (2 * time::delta_time());

		transform.set_rotation(transform.rotation() + scroll);
	});

	game_engine::game_object obj1 = create_game_object();

	obj1.get<component::transform>().set_transform({ 0, 0 }, {50, 50});
	obj1.add<component::rigidBody>();
	obj1.get<component::rigidBody>().intialize(10, 10, {0.25, 0}, "circle");
	obj1.add<component::circle>();
	obj1.add<component::collider_callback>(obj, [](game_engine::game_object& obj, game_engine::game_object& collided) {
		std::cout << "collision!\n";
	});

	game_engine::game_object obj2 = create_game_object();

	obj2.get<component::transform>().set_transform({ 100, 0 }, { 50, 50 });
	obj2.add<component::circle>();
	obj2.add<component::rigidBody>();
	obj2.get<component::rigidBody>().intialize(100, 10, { 0, 0 }, "circle");
}

test_scene::~test_scene()
{
}




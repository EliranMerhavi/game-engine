#include "test_scene.h"


#include "scene/game_object.h"
#include "scene/components.h"

#include "core/input.h"

#include "renderer2D/renderer2D_utils.h"


test_scene::test_scene()
{
}

struct camera_controls_data {
	float zoom_level = 1.0f;
	float camera_speed = 1.0f;
};

struct last_mouse_state {
	input::state state;
};

void test_scene::on_create()
{
	game_engine::game_object camera = create_game_object();
	
	camera.add<component::camera>(-250, 250, -250, 250);
	camera.add<camera_controls_data>();
	camera.get<component::camera>().select_camera();
	camera.add<component::update_callback>(camera, [](game_engine::game_object& camera) {
		auto& transform   = camera.get<component::transform>();
		auto& camera_comp = camera.get<component::camera>();
		auto& data		  = camera.get<camera_controls_data>();

		glm::f32vec2 update = { 0, 0 };
		update.y += ((input::get_key_state(key::W) == input::state::PRESSED) - (input::get_key_state(key::S) == input::state::PRESSED));
		update.x += ((input::get_key_state(key::D) == input::state::PRESSED) - (input::get_key_state(key::A) == input::state::PRESSED));
		update *= time::delta_time();

		float scroll = input::get_mouse_scroll_offset();
		
		if (scroll < 0) {
			data.zoom_level = data.zoom_level + 0.5f;
		}
		else if (scroll > 0) {
			data.zoom_level = data.zoom_level - 0.5f;
		}

		glm::f32vec4 arr = { camera_comp.left(), camera_comp.right(), camera_comp.bottom(), camera_comp.top() };
		arr = data.zoom_level * arr;
		data.zoom_level = 1.0f;
		
		camera_comp.set_projection(arr[0], arr[1], arr[2], arr[3]);
		transform.set_position(transform.position() + data.camera_speed * update);
	});

	tex_id1 = renderer2D::utils::load_texture("assets/images/container.jpg");
	tex_id2 = renderer2D::utils::load_texture("assets/images/image.png");

	for (int i = 0; i < 10; i++) {
		create_texture();
		create_quad();
	}
}

void test_scene::create_texture()
{
	game_engine::game_object obj = create_game_object();

	obj.get<component::transform>().set_transform({ 250 - rand() % 500, 250 - rand() % 500 }, { 20, 20 });
	obj.add<component::texture>((rand() % 2) ? tex_id1 : tex_id2);
	obj.add<last_mouse_state>(input::state::RELEASED);
	obj.add<component::update_callback>(obj, [](game_engine::game_object& obj) {
		test_scene* current_scene = (test_scene*)obj.scene();
		
		auto& transform = obj.get<component::transform>();
		auto& state = obj.get<last_mouse_state>();

		const auto& pos = transform.position();
		auto bottom_right = current_scene->to_world_position(glm::f32vec2{ game_engine::config::window_width() , game_engine::config::window_height() });
		auto top_left = current_scene->to_world_position(glm::f32vec2{ 0, 0 });

		transform.set_rotation(fmod(transform.rotation() + time::delta_time(), 360.0f));

	});
}

void test_scene::create_quad()
{
	game_engine::game_object obj = create_game_object();

	obj.get<component::transform>().set_transform({ 250 - rand() % 500, 250 - rand() % 500 }, { 20, 20 });
	obj.add<component::quad>(glm::f32vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	obj.add<last_mouse_state>(input::state::RELEASED);
	obj.add<component::update_callback>(obj, [](game_engine::game_object& obj) {
		test_scene* current_scene = (test_scene*)obj.scene();

		auto& transform = obj.get<component::transform>();
		auto& state = obj.get<last_mouse_state>();

		const auto& pos = transform.position();
		auto bottom_right = current_scene->to_world_position(glm::f32vec2{ game_engine::config::window_width() , game_engine::config::window_height() });
		auto top_left = current_scene->to_world_position(glm::f32vec2{ 0, 0 });

	});
}

test_scene::~test_scene()
{
	renderer2D::free_texture(tex_id1);
	renderer2D::free_texture(tex_id2);
}




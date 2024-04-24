#include "performance_test.h"
#include "scene/game_object_t.h"
#include "scene/components.h"
#include "core/input.h"
#include <iostream>

#define SIZE 10
#define rand_value() ((rand() % 255) / 255.0f)

performance_test::performance_test() : count(0)
{
}

void performance_test::gui_render()
{
	const auto [width,		height		] = ImGui::GetWindowSize();
	const auto [text_width, text_height	] = ImGui::CalcTextSize("hello    ");

	ImGui::SetCursorPos({ width - 2 * text_width, height - text_height });
	ImGui::Text("hello %d", count);
}

void performance_test::on_remove_quad()
{
	count++;
}

void performance_test::on_load_resources()
{
	add_resource_search_path("assets/images/");
	load_resource<resource::texture_t>("image.png", false);
}

void performance_test::on_create()
{
	game_object_t& camera = create_game_object();
	
	camera.add<component::camera>(-500, 500, -500, 500);
	camera.get<component::camera>().select_camera();
	camera.add<component::update_callback>([](game_object_t& obj) {
		auto* scene = obj.scene();
		
		auto& transform = obj.get<component::transform>();
		glm::f32vec2 update{ 0, 0 };

		if (input::key_state(key::A) == input::state::PRESSED) {
			update.x -= time::delta_time();
		}

		if (input::key_state(key::D) == input::state::PRESSED) {
			update.x += time::delta_time();
		}

		if (input::key_state(key::W) == input::state::PRESSED) {
			update.y += time::delta_time();
		}

		if (input::key_state(key::S) == input::state::PRESSED) {
			update.y -= time::delta_time();
		}

		transform.set_position(transform.position() + update);
	});
	
	int n = 10, m = 10;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			create_object({ i * SIZE, j * SIZE });
		}
	}
}

#define rand_value() (1.0f)

void performance_test::create_object(const glm::f32vec2& pos)
{
	game_object_t& obj = create_game_object();
	auto& tex1 = resource<resource::texture_t>("image.png");

	obj.get<component::transform>().set_data(pos, { SIZE, SIZE });
	obj.add<component::quad>(rand_value(), rand_value(), rand_value(), 1.0f, &tex1);
	obj.add<component::update_callback>([](game_object_t& obj) {
		auto* scene = (performance_test*)obj.scene();
		auto& transform = obj.get<component::transform>();
		
		auto mouse_pos = scene->to_world_position(input::mouse_position());

		if (input::mouse_state(mouse::BUTTON1) != input::state::PRESSED) {
			return;
		}

		if (glm::length(mouse_pos - transform.position()) >= SIZE) {
			return;
		}

		scene->destroy_game_object(obj);
		scene->on_remove_quad();
	});
}
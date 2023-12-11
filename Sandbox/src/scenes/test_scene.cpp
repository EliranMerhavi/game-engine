#include "test_scene.h"
#include "scene/game_object_t.h"
#include "scene/components.h"
#include "glm/gtx/rotate_vector.hpp"
#include "core/input.h"
#include "../components.h"


test_scene::test_scene()
{
}

void test_scene::on_create()
{
	game_object_t camera = create_game_object();

	camera.add<component::camera>(0, game_engine::config::window_width(), 0, game_engine::config::window_height());
	camera.get<component::camera>().select_camera();

	game_object_t left = create_game_object(),
				  right = create_game_object(),
				  bottom = create_game_object(),
				  top = create_game_object();

	left.add<component::quad>();
	left.get<component::transform>().set_transform({0, game_engine::config::window_height() / 2.0f }, {50,  game_engine::config::window_height()});
	left.add<component::rigidBody>(10, 0, glm::f32vec2{0, 0}, true, true);


	right.add<component::quad>();
	right.get<component::transform>().set_transform({ game_engine::config::window_width(), game_engine::config::window_height() / 2.0f }, { 50,  game_engine::config::window_height() });
	right.add<component::rigidBody>(10, 0, glm::f32vec2{ 0, 0 }, true, true);


	bottom.add<component::quad>();
	bottom.get<component::transform>().set_transform({ game_engine::config::window_width() / 2.0f, 0 }, { game_engine::config::window_width(), 50 });
	bottom.add<component::rigidBody>(10, 0, glm::f32vec2{ 0, 0 }, true, true);
	
	top.add<component::quad>();
	top.get<component::transform>().set_transform({ game_engine::config::window_width() / 2.0f, game_engine::config::window_height()  }, {game_engine::config::window_width(), 50});
	top.add<component::rigidBody>(10, 0, glm::f32vec2{ 0, 0 }, true, true);


	create_ball({50, game_engine::config::window_height() / 2});
}

void test_scene::create_obstacle(const glm::f32vec2& pos, const glm::f32vec2& size, obstacle_t type, bool is_dynamic, float bounciness)
{



}

void test_scene::create_ball(const glm::f32vec2& pos)
{
	game_object_t obj = create_game_object("Ball");

	obj.get<component::transform>().set_transform(pos, {20, 20});
	
	obj.add<component::circle>(glm::f32vec4{ 1.0f, 0.0f,0.0f ,1.0f });
	
	obj.add<ball_data_t>(ball_data_t{input::state::RELEASED});
	
	obj.add<component::rigidBody>(2, 0, glm::f32vec2{0, 0}, false, false);

	obj.add<component::update_callback>(obj, [](game_object_t& obj) {
		test_scene* scene = (test_scene*)obj.scene();
		
		auto& transform = obj.get<component::transform>();
		auto& rigid_body = obj.get<component::rigidBody>();
		auto& data = obj.get<ball_data_t>();

		const auto& pos = transform.position();
		const auto& scale = transform.scale();
		auto mouse_pos = scene->to_world_position(input::mouse_position());
		auto mouse_state = input::mouse_state(mouse::BUTTON1);

		// for different balls use different number from 1.25 between (1, 2)

		rigid_body.velocity *= 1.0f / (1 + exp(-1.25f * glm::length(rigid_body.velocity)));


		if (mouse_state == data.last_state) {
			return;
		}

		if (mouse_state == input::state::PRESSED) {
			if (glm::length(pos - mouse_pos) < scale.x / 2) {
				scene->create_animation(mouse_pos, pos);
				data.last_state = input::state::PRESSED;
			}
		}
		else { // mouse is released
			auto x = glm::length(pos - mouse_pos);
			auto direction = (pos - mouse_pos) / x;

			rigid_body.velocity = direction * (5.0f / (1 + exp(-x)));

			data.last_state = input::state::RELEASED;
		}
	});
}

void test_scene::create_animation(const glm::f32vec2& mouse_pos_in_world, const glm::f32vec2& ball_pos)
{

}

void test_scene::create_goal(const glm::f32vec2& pos, const glm::f32vec2& size)
{

}

test_scene::~test_scene()
{	
}
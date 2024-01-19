#include "test_scene.h"
#include "scene/game_object_t.h"

#include "glm/gtx/rotate_vector.hpp"
#include "core/input.h"
#include "../components.h"


test_scene::test_scene(level_loader_t level0) : m_level0(level0)
{
}

void test_scene::on_load_resources()
{
}

void test_scene::on_create()
{
	int width = game_engine::config::window_width(),
		height = game_engine::config::window_height();

	game_object_t camera = create_game_object();
	
	camera.add<component::camera>(0, width, 0, height);
	camera.get<component::camera>().select_camera();

	/* the obstacle stuff */
	
	m_level0(*this);

	/* end obstacle stuff */

	add_border({ 0, height / 2.0f }, { 50,  height }); 
	add_border({ width, height / 2.0f }, { 50, height });
	add_border({ width / 2.0f, 0 }, { width, 50 });
	add_border({ width / 2.0f, height }, { width, 50 });
}

void test_scene::load_level(level_loader_t loader)
{
	clear_level();
	loader(*this);
}

void test_scene::add_border(const glm::f32vec2& pos, const glm::f32vec2& size)
{
	game_object_t& border = create_game_object();
	border.add<component::quad>();
	border.get<component::transform>().set_data(pos, size);
	border.add<component::rigidBody>(collisions::type::ROTATIONAL, 10, 0, glm::f32vec2{ 0, 0 }, true, true);
}

void test_scene::create_obstacle(obstacle_t type, const glm::f32vec2& pos, const glm::f32vec2& size, const component::rigidBody& rigid_body)
{
	game_object_t& obj = create_game_object("Obstacle");

	obj.get<component::transform>().set_data(pos, size);
	switch (type)
	{
	case obstacle_t::CIRCLE:
		obj.add<component::circle>();
		break;
	case obstacle_t::RECT:
		obj.add<component::quad>();
		break;
	}
	obj.add<component::rigidBody>(rigid_body);
}

void test_scene::create_ball(const glm::f32vec2& pos)
{
	game_object_t& obj = create_game_object("Ball");

	obj.get<component::transform>().set_data(pos, {20, 20});
	
	obj.add<component::circle>(1.0f, 0.0f,0.0f ,1.0f);
	
	obj.add<ball_data_t>(input::state::RELEASED);
	
	obj.add<component::rigidBody>(collisions::type::ROTATIONAL, 2, 0, glm::f32vec2{0, 0}, false, false);

	obj.add<component::update_callback>([](game_object_t& obj) {
		test_scene* scene = (test_scene*)obj.scene();
		auto& rigid_body = obj.get<component::rigidBody>();
		auto& data = obj.get<ball_data_t>();

		const auto& [pos, scale, rotation] = obj.get<component::transform>().data();

		auto mouse_pos = scene->to_world_position(input::mouse_position());
		auto mouse_state = input::mouse_state(mouse::BUTTON1);

		// for different balls use different number from 1.25 between (1, 2)

		rigid_body.velocity *= time::delta_time() / (1 + exp(-2.0f * glm::length(rigid_body.velocity)));
		
		if (mouse_state == data.last_state) {
			return;
		}

		if (mouse_state != input::state::PRESSED) {
			auto x = glm::length(pos - mouse_pos);
			auto direction = (pos - mouse_pos) / x;

			rigid_body.velocity = direction * (5.0f / (1 + exp(-x)));

			data.last_state = input::state::RELEASED;
			return;
		}
		
		if (glm::length(pos - mouse_pos) < scale.x / 2) { // mouse is pressed
			scene->create_animation(mouse_pos, pos);
			data.last_state = input::state::PRESSED;
		}
	});
}

void test_scene::create_animation(const glm::f32vec2& mouse_pos_in_world, const glm::f32vec2& ball_pos)
{

}

void test_scene::create_goal(const glm::f32vec2& pos, const glm::f32vec2& size)
{
	game_object_t obj = create_game_object("Goal");

	obj.get<component::transform>().set_data(pos, { 20, 20 });

	obj.add<component::circle>(1.0f, 1.0f, 0.0f ,1.0f);
	obj.add<ball_data_t>(input::state::RELEASED);

	obj.add<component::rigidBody>(collisions::type::IGNORED, 2, 0, glm::f32vec2{ 0, 0 }, true, true);

	obj.add<component::collider_callback>([](game_object_t& obj, game_object_t& collided) {
			
	});
}

void test_scene::clear_level()
{
	
}

test_scene::~test_scene()
{	
}
#include "pch.h"
#include "scene.h"

#include "scene/components.h"

#include "renderer2D/renderer2D.h"
#include "physics2D/phsyics.h"
#include "game_object.h"


game_engine::scene::scene() : m_registry(), system(*this), m_camera_id((ecs::entity_t)-1)
{
	auto main_camera = create_game_object();
	main_camera.add<component::camera>(-0.5f, 0.5f, -0.5f, 0.5f);
	main_camera.get<component::camera>().select_camera();
	calculate_camera_matrix();
}

game_engine::scene::~scene()
{
}

game_engine::game_object game_engine::scene::create_game_object()
{
	game_object object(*this);
	object.add<component::transform>();
	return object;
}

game_engine::game_object game_engine::scene::create_game_object(const std::string& tag)
{
	game_object object = create_game_object();
	object.add<component::tag>(tag);
	return object;
}

game_engine::game_object game_engine::scene::get_game_object_by_tag(const std::string& tag)
{
	for (auto entity : m_registry.pool<component::tag>().entities()) {
		if (m_registry.get<component::tag>(entity).str() == tag) {
			return game_engine::game_object(entity, *this);
		}
	}
	
	throw std::exception("couldnt find entity with the tag");
}

glm::f32vec2 game_engine::scene::to_world_position(const glm::f32vec2& screen_position)
{
	calculate_camera_matrix();

	glm::f32vec2 res = screen_position;

	res.x = -1 + 2 * res.x / game_engine::config::window_width();
	res.y =  1 - 2 * res.y / game_engine::config::window_height();
	
	res = glm::inverse(m_camera_matrix) * glm::f32vec4(res, 0, 1);
	
	return res;
}

void game_engine::scene::render()
{
	calculate_camera_matrix();

	renderer2D::set_camera(m_camera_matrix);
	
	for (ecs::entity_t entity : m_registry.pool<component::quad>().entities()) {
		auto& transform = m_registry.get<component::transform>(entity);
		auto& quad = m_registry.get<component::quad>(entity);
		renderer2D::set_color(quad.color());
		renderer2D::quad(transform.matrix());
	}

	for (ecs::entity_t entity : m_registry.pool<component::circle>().entities()) {
		auto& transform = m_registry.get<component::transform>(entity);
		auto& circle = m_registry.get<component::circle>(entity);
		renderer2D::set_color(circle.color());
		renderer2D::circle(transform.matrix());
	}

	for (ecs::entity_t entity : m_registry.pool<component::texture>().entities()) {
		auto& transform = m_registry.get<component::transform>(entity);
		auto& texture = m_registry.get<component::texture>(entity);

		renderer2D::texture(texture.id(), transform.matrix());
	}

	for (const auto& callback : m_registry.pool<component::render_callback>().data()) {
		callback.render();
	}
}

void game_engine::scene::update()
{
	for (const auto& callback : m_registry.pool<component::update_callback>().data()) {
		callback.update();
	}
	system.update();
}

void game_engine::scene::calculate_camera_matrix()
{
	if (m_camera_id == (ecs::entity_t)-1 || !m_registry.get<component::camera>(m_camera_id).is_selected()) 
	{
		for (auto entity : m_registry.pool<component::camera>().entities())
		{
			auto& camera = m_registry.get<component::camera>(entity);
			if (camera.is_selected())
			{
				m_camera_id = entity;
				break;
			}
		}
	}

	assert(m_camera_id != (ecs::entity_t)-1 && m_registry.get<component::camera>(m_camera_id).is_selected()); // there is no camera
	
	auto& transform = m_registry.get<component::transform>(m_camera_id);
	auto& camera = m_registry.get<component::camera>(m_camera_id);

	m_camera_matrix = camera.projection() * glm::inverse(transform.matrix());
}

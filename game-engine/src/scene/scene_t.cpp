#include "pch.h"
#include "scene_t.h"

#include "scene/components.h"

#include "renderer2D/renderer2D.h"
#include "physics2D/phsyics.h"
#include "game_object_t.h"


scene_t::scene_t() : 
	m_registry(), 
	m_physics_system(*this), 
	m_resource_system(),
	m_selected_camera_data{.camera_id=(ecs::entity_t)-1}
{
	auto main_camera = create_game_object();
	main_camera.add<component::camera>(-0.5f, 0.5f, -0.5f, 0.5f);
	main_camera.get<component::camera>().select_camera();
	calculate_camera_matrix();
}

scene_t::~scene_t()
{
}

game_object_t& scene_t::create_game_object()
{
	ecs::entity_t id = m_registry.create();
	m_game_objects.emplace(id, game_object_t(id, *this));
	m_game_objects.at(id).add<component::transform>();
	return m_game_objects.at(id);
}

game_object_t& scene_t::create_game_object(const std::string& tag)
{
	game_object_t& object = create_game_object();
	object.add<component::tag>(tag);
	return object;
}

void scene_t::destroy_game_object(const game_object_t& object)
{
	m_registry.destroy(object.id());
	m_game_objects.erase(object.id());
}

void scene_t::add_resource_search_path(const std::string& path)
{
	m_resource_system.add_search_path(path);
}

game_object_t& scene_t::get_game_object_by_tag(const std::string& tag)
{
	for (auto entity : m_registry.entities<component::tag>()) {
		if (m_registry.get<component::tag>(entity).str() == tag) {
			return m_game_objects.at(entity);
		}
	}
	throw std::exception("couldnt find entity with the tag");
}

game_object_t& scene_t::get_game_object(ecs::entity_t id)
{
	return m_game_objects.at(id);
}

game_object_t& scene_t::clone_game_object(ecs::entity_t id)
{
	ecs::entity_t cloned_id = m_registry.clone(id);
	m_game_objects.emplace(cloned_id, game_object_t(cloned_id, *this));
	return m_game_objects.at(cloned_id);
}

glm::f32vec2 scene_t::to_world_position(const glm::f32vec2& screen_position)
{
	const auto& [window_width, window_height] = game_engine::config::window_size();
	calculate_camera_matrix();

	glm::f32vec2 res = screen_position;

	res.x = -1 + 2 * res.x / window_width;
	res.y =  1 - 2 * res.y / window_height;
	
	res = m_selected_camera_data.inverse_camera_matrix_cache * glm::f32vec4(res, 0, 1);
	
	return res;
}

void scene_t::gui_render()
{
}

void scene_t::render()
{
	calculate_camera_matrix();
	renderer2D::set_camera(m_selected_camera_data.camera_matrix_cache);

	for (ecs::entity_t entity : m_registry.entities<component::quad>()) {
		auto& transform = m_registry.get<component::transform>(entity);
		auto& quad		= m_registry.get<component::quad>(entity);
		renderer2D::quad(transform.matrix(), quad.color(), quad.texture().id(), quad.texture().coords());
	}
	
	for (ecs::entity_t entity : m_registry.entities<component::circle>()) {
		auto& transform = m_registry.get<component::transform>(entity);
		auto& circle    = m_registry.get<component::circle>(entity);
		renderer2D::circle(transform.matrix(), circle.color());
	}
}

void scene_t::update()
{
	for (ecs::entity_t entity : m_registry.entities<component::update_callback>()) {
		if (!m_registry.has<component::update_callback>(entity))
			continue;
		auto& callback = m_registry.get<component::update_callback>(entity);
		callback(get_game_object(entity));
	}
	// m_registry.update();
	m_physics_system.update();
}

void scene_t::calculate_camera_matrix()
{
	auto& [m_camera_id, m_camera_matrix_cache, m_inverse_camera_matrix_cache] = m_selected_camera_data;

	if (m_camera_id == (ecs::entity_t)-1 || !m_registry.get<component::camera>(m_camera_id).is_selected())
	{
		for (auto entity : m_registry.entities<component::camera>())
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

	m_camera_matrix_cache = camera.projection() * glm::inverse(transform.matrix());
	m_inverse_camera_matrix_cache = glm::inverse(m_camera_matrix_cache);
}


#include "pch.h"
#include "scene.h"
#include "ecs/components.h"
#include "game_object.h"
#include "renderer2D/renderer2D.h"


game_engine::scene::scene() : m_registry(), system(m_registry)
{
	auto main_camera = create_game_object();
	main_camera.add<component::camera>(-0.5f, 0.5f, -0.5f, 0.5f);
	main_camera.get<component::camera>().select_camera();
}

game_engine::scene::~scene()
{
}

game_engine::game_object game_engine::scene::create_game_object()
{
	game_object object(this->m_registry);
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
			return game_engine::game_object(entity, m_registry);
		}
	}
	
	throw std::exception("couldnt find entity with the tag");
}


void game_engine::scene::render()
{
	for (auto entity : m_registry.pool<component::camera>().entities())
	{
		auto& camera = m_registry.get<component::camera>(entity);
		if (camera.is_selected()) 
		{
			auto& transform = m_registry.get<component::transform>(entity);
			auto view = glm::inverse(transform.matrix());
			renderer2D::set_camera(camera.projection() * view);
			break;
		}
	}
	
	for (ecs::entity_t entity : m_registry.pool<component::quad>().entities()) {
		auto& transform = m_registry.get<component::transform>(entity);
		auto& quad = m_registry.get<component::quad>(entity);
		renderer2D::set_color(quad.color());
		renderer2D::circle(transform.matrix());
	}

	for (ecs::entity_t entity : m_registry.pool<component::circle>().entities()) {
		auto& transform = m_registry.get<component::transform>(entity);
		auto& circle = m_registry.get<component::circle>(entity);
		renderer2D::set_color(circle.color());
		renderer2D::circle(transform.matrix());
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

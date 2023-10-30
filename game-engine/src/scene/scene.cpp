#include "pch.h"
#include "scene.h"
#include "ecs/components.h"
#include "game_object.h"
#include "renderer2D/renderer2D.h"


game_engine::scene::scene()
{
	auto main_camera = create_game_object();
	main_camera.add<component::camera>(-0.5f, 0.5f, -0.5f, 0.5f);
	main_camera.get<component::camera>().select_camera();
}

game_engine::scene::~scene()
{
	m_registry.clear();
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
	for (auto entity : m_registry.view<component::tag>()) {
		if (m_registry.get<component::tag>(entity).str() == tag) {
			return game_engine::game_object(entity, m_registry);
		}
	}
	
	throw std::exception("couldnt find entity with the tag");
}


void game_engine::scene::render()
{
	if (component::camera::current_camera()) 
	{
		for (auto entity : m_registry.view<component::camera>())
		{
			auto& camera = m_registry.get<component::camera>(entity);
			if (&camera == component::camera::current_camera()) 
			{
				auto& transform = m_registry.get<component::transform>(entity);
				auto view = glm::inverse(transform.matrix());
				renderer2D::set_camera(camera.projection() * view);
				break;
			}
		}
	}

	m_registry.view<component::transform, component::quad>().each([](const entt::entity entity, component::transform& transform, component::quad& quad) {
		renderer2D::set_color(quad.color());
		renderer2D::quad(transform.matrix());
	});

	m_registry.view<component::transform, component::circle>().each([](const entt::entity entity, component::transform& transform, component::circle& circle) {
		renderer2D::set_color(circle.color());
		renderer2D::circle(transform.matrix());
	});

	m_registry.view<component::render_callback>().each([](component::render_callback& callback) {
		callback.render();
	});
}

void game_engine::scene::update()
{
	m_registry.view<component::update_callback>().each([](component::update_callback& callback) {
		callback.update();
	});
}

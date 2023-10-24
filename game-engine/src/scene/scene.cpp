#include "pch.h"
#include "scene.h"
#include "components.h"
#include "game_object.h"
#include "renderer2D/renderer2D.h"


void game_engine::scene::set_primary_camera(const game_engine::game_object& camera)
{
	m_camera_id = camera.id();
}


game_engine::game_object game_engine::scene::create_game_object() 
{
	game_object object(this->m_registry);
	
	object.add<transform_t>();

	return object;
}

void game_engine::scene::render()
{
	renderer2D::set_camera(m_registry.get<camera_component>(m_camera_id).camera());
		
	for (auto entity : m_registry.view<renderable_component>()) 
	{
		m_registry.get<renderable_component>(entity).render();
	}
}

void game_engine::scene::update()
{
	for (auto entity : m_registry.view<updateable_component>()) 
	{
		m_registry.get<updateable_component>(entity).update();
	}
}

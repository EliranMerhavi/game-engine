#include "pch.h"
#include "game_object_t.h"

game_object_t::game_object_t(scene_t& _scene) : 
	m_id(_scene.m_registry.create()), m_scene(&_scene)
{
}

game_object_t::game_object_t(ecs::entity_t id, scene_t& _scene) : m_id(id), m_scene(&_scene)
{
}


ecs::entity_t game_object_t::id() const
{
	return m_id;
}

scene_t* game_object_t::scene()
{
	return m_scene;
}

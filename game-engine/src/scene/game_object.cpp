#include "pch.h"
#include "game_object.h"

game_engine::game_object::game_object(game_engine::scene& _scene) : 
	m_id(_scene.m_registry.create()), m_scene(&_scene)
{
}

game_engine::game_object::game_object(ecs::entity_t id, game_engine::scene& _scene) : m_id(id), m_scene(&_scene)
{
}

game_engine::scene* game_engine::game_object::scene()
{
	return m_scene;
}

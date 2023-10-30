#include "pch.h"
#include "game_object.h"


game_engine::game_object::game_object(entt::registry& registry) : game_engine::game_object(registry.create(), registry)
{
}



void game_engine::game_object::delete_object()
{
    m_registry.destroy(m_id);
}

game_engine::game_object::game_object(entt::entity id, entt::registry& registry) : m_id(id), m_registry(registry)
{
}

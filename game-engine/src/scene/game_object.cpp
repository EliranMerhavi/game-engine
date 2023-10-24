#include "pch.h"
#include "game_object.h"


game_engine::game_object::game_object(entt::registry& registry) : m_id(registry.create()), m_registry(registry)
{
}

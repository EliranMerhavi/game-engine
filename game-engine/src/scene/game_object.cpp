#include "pch.h"
#include "game_object.h"


game_engine::game_object::game_object(ecs::registry& registry) : game_engine::game_object(registry.create(), registry)
{
}



void game_engine::game_object::delete_object()
{

}

game_engine::game_object::game_object(ecs::entity_t id, ecs::registry& registry) : m_id(id), m_registry(registry)
{
}

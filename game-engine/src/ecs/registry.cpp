#include "pch.h"
#include "registry.h"

ecs::entity_t ecs::registry::create()
{
	ecs::entity_t entity = m_entity_counter;
	m_entity_counter = (ecs::entity_t)(((size_t)m_entity_counter + 1) % SIZE_MAX);
	return entity;
}


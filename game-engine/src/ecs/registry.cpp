#include "pch.h"
#include "registry.h"
#include "../scene/components.h"

ecs::registry::registry() : m_pools(), m_entity_counter()
{

}

ecs::entity_t ecs::registry::create()
{
	ecs::entity_t entity = m_entity_counter;
	m_entity_counter = (ecs::entity_t)(((size_t)m_entity_counter + 1) % SIZE_MAX);
	return entity;
}

ecs::entity_t ecs::registry::clone(ecs::entity_t entity)
{
	ecs::entity_t res = create();
	for (auto& [hash_code, comp_pool] : m_pools) {
		if (comp_pool.has(entity)) {
			comp_pool.copy(entity, res);
		}
	}
	return res;
}

void ecs::registry::update()
{
	for (auto& [hash_code, comp_pool] : m_pools) {
		comp_pool.update();	
	}
}

void ecs::registry::destroy(ecs::entity_t entity)
{
	for (auto& [hash_code, comp_pool] : m_pools) {
		if (comp_pool.has(entity)) {
			comp_pool.remove(entity);
		}
	}
}


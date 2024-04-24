#include "pch.h"
#include "components_pool.h"
#include "../scene/components.h"

ecs::components_pool::components_pool() : m_components(), m_rev_index_table(), m_index_table() 
{
}

bool ecs::components_pool::has(ecs::entity_t entity) const
{
	return m_index_table.count(entity);
}

void ecs::components_pool::copy(ecs::entity_t from, ecs::entity_t to)
{
	assert(has(from) && !has(to));

	m_index_table[to] = m_components.size();
	m_rev_index_table.push_back(to);

	m_components.emplace_back(m_components[m_index_table[from]]);
}

void ecs::components_pool::remove(ecs::entity_t entity)
{
	assert(has(entity));
	
	int i = m_index_table[entity];

	m_components[i] = m_components.back();
	m_index_table[m_rev_index_table.back()] = i;
	std::swap(m_rev_index_table[i], m_rev_index_table.back());

	m_components.pop_back();
	m_rev_index_table.pop_back();
	m_index_table.erase(entity);
}

void ecs::components_pool::update()
{

}

std::span<const ecs::entity_t> ecs::components_pool::entities() const
{
	return std::span(m_rev_index_table.begin(), m_rev_index_table.end());
}

size_t ecs::components_pool::size() const
{
	return m_components.size();
}
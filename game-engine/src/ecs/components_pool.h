#pragma once
#include "entity.h"
#include <assert.h>
#include <unordered_map>
#include <functional>

namespace ecs
{
	template<typename t>
	class components_pool 
	{
		template<typename k, typename v>
		using straight_map = std::unordered_map<k, v>;
	public:
		components_pool() : m_components(), m_rev_index_table(), m_index_table()
		{
		}

		bool has(ecs::entity_t entity) const
		{
			return m_index_table.count(entity);
		}

		t& get(ecs::entity_t entity) const
		{
			assert(has(entity));
			return m_components.at(m_index_table.at(entity));
		}

		template<typename... args_t>
		void emplace(ecs::entity_t entity, args_t... args)
		{
			assert(!has(entity));
			m_index_table[entity] = m_components.size();
			m_rev_index_table.push_back(entity);
			m_components.emplace_back(std::forward<args_t>(args)...);
		}

		void remove(ecs::entity_t entity)
		{
			assert(has(entity));
			
			int i = m_index_table[entity];
			
			m_components[i] = m_components.back();
			m_index_table[m_rev_index_table.back()] = i;
			m_rev_index_table[i] = m_rev_index_table.back();

			m_components.pop_back();
			m_rev_index_table.pop_back();
			m_index_table.erase(entity);
		}

		const std::vector<t>& data() const
		{
			return m_components;
		}
		
		const std::vector<ecs::entity_t>& entities() const
		{
			return m_rev_index_table;
		}

	private:
		mutable std::vector<t> m_components;
		std::vector<ecs::entity_t> m_rev_index_table;
		straight_map<ecs::entity_t, int> m_index_table;
	};
}

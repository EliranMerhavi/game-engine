#pragma once

#include "entity.h"
#include <assert.h>
#include <unordered_map>
#include <functional>
#include <span>

namespace ecs
{
	class components_pool 
	{
		template<typename k, typename v>
		using straight_map = std::unordered_map<k, v>;
	public:
		components_pool();

		bool has(ecs::entity_t entity) const
		{
			return m_index_table.count(entity);
		}

		template<typename t>
		t& get(ecs::entity_t entity) const
		{
			assert(has(entity));
			return std::any_cast<t&>(m_components.at(m_index_table.at(entity)));
		}

		template<typename t, typename... args_t>
		void emplace(ecs::entity_t entity, args_t... args)
		{
			assert(!has(entity));
			m_index_table[entity] = m_components.size();
			m_rev_index_table.push_back(entity);
			m_components.emplace_back(t(std::forward<args_t>(args)...));
		}

		void copy(ecs::entity_t from, ecs::entity_t to)
		{
			assert(has(from) && !has(to));
			
			m_index_table[to] = m_components.size();
			m_rev_index_table.push_back(to);
			
			m_components.emplace_back(m_components[m_index_table[from]]);
		}

		void remove(ecs::entity_t entity)
		{
			assert(has(entity));
			
			int i = m_index_table[entity];
			
			m_components[i] = m_components.back();
			m_index_table[m_rev_index_table.back()] = i;

			m_components.pop_back();
			m_rev_index_table.pop_back();
			m_index_table.erase(entity);
		}

		template<typename t>
		std::vector<t> data() const
		{
			size_t n = size();
			std::vector<t> res;

			for (int i = 0; i < n; i++) 
			{
				res.emplace_back(std::any_cast<const t>(m_components[i]));
			}

			return res;
		}
		
		std::span<const ecs::entity_t> entities() const
		{
			return std::span(m_rev_index_table.begin(), m_rev_index_table.end());
		}

		size_t size() const 
		{
			return m_components.size();
		}

	private:
		mutable std::vector<std::any> m_components;
		std::vector<ecs::entity_t> m_rev_index_table;
		straight_map<ecs::entity_t, int> m_index_table;
	};
}

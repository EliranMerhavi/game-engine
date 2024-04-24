#pragma once

#include "entity.h"
#include <assert.h>
#include <unordered_map>
#include <functional>
#include <span>
#include <iostream>

#include "../scene/components/quad.h"

namespace ecs
{
	class components_pool 
	{
		template<typename k, typename v>
		using straight_map = std::unordered_map<k, v>;
	public:
		components_pool();

		bool has(ecs::entity_t entity) const;
		void copy(ecs::entity_t from, ecs::entity_t to);
		void remove(ecs::entity_t entity);
		void update();

		std::span<const ecs::entity_t> entities() const;
		size_t size() const;

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

		template<typename t>
		std::vector<t> data() const
		{
			size_t n = size();
			std::vector<t> res;
			for (int i = 0; i < n; i++)
				res.emplace_back(std::any_cast<const t>(m_components[i]));
			return res;
		}

	private:
		mutable std::vector<std::any> m_components;
		std::vector<ecs::entity_t> m_rev_index_table;
		straight_map<ecs::entity_t, int> m_index_table;
		size_t update_pos, add_pos;
	};
}

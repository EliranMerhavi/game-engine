#pragma once

#include <assert.h>
#include <any>
#include <unordered_map>

#include "entity.h"
#include "components_pool.h"

namespace ecs
{
	class registry
	{
	public:
		
		registry() : m_pools(), m_entity_counter()
		{
		}

		ecs::entity_t create();

		template<typename component_t>
		bool has(ecs::entity_t entity) const
		{
			return has_pool<component_t>() && pool<component_t>().has(entity);
		}

		template<typename component_t, typename... args_t>
		void emplace(ecs::entity_t entity, args_t... args)
		{
			get_pool<component_t>().emplace(entity, std::forward<args_t>(args)...);
		}

		template<typename component_t>
		void remove(ecs::entity_t entity)
		{
			get_pool<component_t>().remove(entity);
		}

		template<typename component_t>
		component_t& get(ecs::entity_t entity) const
		{
			return pool<component_t>().get(entity);
		}

		template<typename component_t>
		const components_pool<component_t>& pool() const
		{
			assure_pool<component_t>();
			return std::any_cast<const components_pool<component_t>&>(m_pools.at(typeid(component_t).hash_code()));
		}

	private:
		
		template<typename component_t>
		components_pool<component_t>& get_pool()
		{
			assure_pool<component_t>();
			return std::any_cast<components_pool<component_t>&>(m_pools[typeid(component_t).hash_code()]);
		}

		template<typename component_t>
		void assure_pool() const
		{
			if (!has_pool<component_t>())
				m_pools[typeid(component_t).hash_code()] = ecs::components_pool<component_t>();
		}

		template<typename component_t>
		bool has_pool() const
		{
			return m_pools.count(typeid(component_t).hash_code());
		}

		mutable std::unordered_map<size_t, std::any> m_pools;
		ecs::entity_t m_entity_counter; // TODO: system for entities
	};
}
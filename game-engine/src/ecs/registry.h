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
		
		registry();

		ecs::entity_t create();
		ecs::entity_t clone(ecs::entity_t entity);

		void destroy(ecs::entity_t entity);
	
		template<typename component_t>
		void copy(ecs::entity_t from, ecs::entity_t to)
		{
			assert(has<component_t>(from));
			get_pool<component_t>().copy(from, to);
		}

		template<typename component_t>
		bool has(ecs::entity_t entity) const
		{
			return has_pool<component_t>() && get_pool<component_t>().has(entity);
		}

		template<typename component_t, typename... args_t>
		void emplace(ecs::entity_t entity, args_t... args)
		{
			get_pool<component_t>().emplace<component_t, args_t...>(entity, std::forward<args_t>(args)...);
		}

		template<typename component_t>
		void remove(ecs::entity_t entity)
		{
			get_pool<component_t>().remove(entity);
		}

		template<typename component_t>
		component_t& get(ecs::entity_t entity) const
		{
			return get_pool<component_t>().get<component_t>(entity);
		}

		template<typename component_t>
		std::vector<component_t> data() const
		{
			assure_pool<component_t>();
			
			return get_pool<component_t>().data<component_t>();
		}

		template<typename component_t>
		std::span<const ecs::entity_t> entities() const
		{
			assure_pool<component_t>();

			return get_pool<component_t>().entities();
		}

	private:
		template<typename component_t>
		const components_pool& get_pool() const
		{
			assure_pool<component_t>();
			return m_pools.at(typeid(component_t).hash_code());
		}

		template<typename component_t>
		components_pool& get_pool()
		{
			assure_pool<component_t>();
			return m_pools[typeid(component_t).hash_code()];
		}

		template<typename component_t>
		void assure_pool() const
		{
			if (!has_pool<component_t>())
				m_pools[typeid(component_t).hash_code()] = ecs::components_pool();
		}

		template<typename component_t>
		bool has_pool() const
		{
			return m_pools.count(typeid(component_t).hash_code());
		}

		mutable std::unordered_map<size_t, components_pool> m_pools;
		ecs::entity_t m_entity_counter; // TODO: system for entities
		
	};
}
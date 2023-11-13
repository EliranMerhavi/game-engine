#pragma once

#include "ecs/components.h"
#include "ecs/registry.h"
#include "ecs/entity.h"

namespace game_engine
{
	class game_object
	{
	public:
		game_object(const game_object&) = default;
		game_object(ecs::entity_t id, ecs::registry& registry);
		game_object(ecs::registry& registry);
		

		template<typename T, typename... args_t>
		void add(args_t... args)
		{
			m_registry.emplace<T>(m_id, std::forward<args_t>(args)...);
		}

		template<typename T>
		T& get() const
		{
			return m_registry.get<T>(m_id);
		}

		void delete_object();
		ecs::entity_t id() const { return m_id; }
	private:
		ecs::entity_t m_id;
		ecs::registry& m_registry;
	};
}

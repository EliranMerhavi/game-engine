#pragma once

#include "ecs/components.h"
#include "entt/entt.hpp"

namespace game_engine
{
	class game_object
	{
	public:
		game_object(const game_object&) = default;
		game_object(entt::entity id, entt::registry& registry);
		game_object(entt::registry& registry);
		

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
		entt::entity id() const { return m_id; }
	private:
		entt::entity m_id;
		entt::registry& m_registry;
	};
}

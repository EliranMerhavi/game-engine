#pragma once

#include <functional>
#include <unordered_map>
#include <type_traits>
#include <string>
#include "scene/components.h"

#include "entt/entt.hpp"
#include "scene.h"

namespace game_engine
{
	class component;

	class game_object
	{
	public:
		game_object(const game_object&) = default;
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

		entt::entity id() const { return m_id; }
	private:
		entt::entity m_id;
		entt::registry& m_registry;
	};
}

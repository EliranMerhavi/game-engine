#pragma once

#include "ecs/registry.h"
#include "ecs/entity.h"
#include "scene/scene.h"

namespace game_engine
{
	class game_object
	{
	public:
		game_object(const game_object&) = default;
		game_object(scene& _scene);
		game_object(ecs::entity_t id, scene& _scene);
		
		scene& scene();

		template<typename T>
		bool has() const
		{
			return m_scene.m_registry.has<T>(m_id);
		}

		template<typename T, typename... args_t>
		void add(args_t... args)
		{
			m_scene.m_registry.emplace<T>(m_id, std::forward<args_t>(args)...);
		}

		template<typename T>
		T& get() const
		{
			return m_scene.m_registry.get<T>(m_id);
		}

		ecs::entity_t id() const { return m_id; }
	private:
		ecs::entity_t m_id;
		game_engine::scene& m_scene;
	};
}

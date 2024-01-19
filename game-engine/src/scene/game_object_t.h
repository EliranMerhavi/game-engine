#pragma once

#include "ecs/registry.h"
#include "ecs/entity.h"
#include "scene/scene_t.h"

class game_object_t
{
public:
	game_object_t(scene_t& _scene);
	game_object_t(ecs::entity_t id, scene_t& _scene);
		
	game_object_t& clone();
	
	ecs::entity_t id() const;
	scene_t* scene();


	template<typename T>
	bool has() const
	{
		return m_scene->m_registry.has<T>(m_id);
	}

	template<typename T, typename... args_t>
	void add(args_t... args)
	{
		m_scene->m_registry.emplace<T>(m_id, std::forward<args_t>(args)...);
	}

	template<typename T>
	T& get() const
	{
		return m_scene->m_registry.get<T>(m_id);
	}

private:
	ecs::entity_t m_id;
	scene_t* m_scene;
};


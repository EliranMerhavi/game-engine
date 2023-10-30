#pragma once

#include "entt/entt.hpp"
#include "game_object.h"
#include "game_engine.h"

namespace game_engine
{
	class scene
	{
	public:
		scene();
		~scene();
		virtual void on_create() = 0;
		game_object create_game_object();
		game_object create_game_object(const std::string& tag);
		game_object get_game_object_by_tag(const std::string& tag);

	private:
		void render();
		void update();
	private:
		entt::registry m_registry;

		friend void game_engine::run();
	};
}



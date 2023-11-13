#pragma once

#include "ecs/registry.h"
#include "game_object.h"
#include "game_engine.h"
#include "physics2D/phsyics.h"

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
		ecs::registry m_registry;
		phsyics2D_system system;

		friend void game_engine::run();
	};
}



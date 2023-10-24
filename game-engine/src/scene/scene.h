#pragma once

#include "core/config.h"
#include "entt/entt.hpp"

namespace game_engine
{
	void run(const config_t& config);
	class game_object;

	class scene
	{
	public:
		virtual void on_create() = 0;
		game_object create_game_object();
		
	private:
		void render();
		void update();
	protected:
		void set_primary_camera(const game_object& camera);
	private:
		entt::registry m_registry;
		entt::entity m_camera_id;
		friend void game_engine::run(const config_t& config);
		friend class game_object;
	};
}



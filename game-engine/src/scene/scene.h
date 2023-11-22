#pragma once

#include "ecs/registry.h"
#include "game_engine.h"
#include "glm/glm.hpp"
#include "physics2D/phsyics.h"

namespace game_engine
{
	class game_object;
	class scene
	{
		friend void game_engine::run();
		friend class game_object;
		friend class phsyics2D_system;
	public:
		scene();
		~scene();
		virtual void on_create() = 0;
		
		game_engine::game_object create_game_object();
		game_engine::game_object create_game_object(const std::string& tag);
		game_engine::game_object get_game_object_by_tag(const std::string& tag);

		glm::f32vec2 to_world_position(const glm::f32vec2& screen_position);
	private:
		game_engine::game_object get_camera_object();
		void render();
		void update();
		void calculate_camera_matrix();
	private:
		ecs::registry m_registry;
		phsyics2D_system system;
		ecs::entity_t m_camera_id;
		glm::mat4 m_camera_matrix;
	};
}




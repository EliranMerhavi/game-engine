#pragma once


#include "ecs/registry.h"
#include "game_engine.h"
#include "glm/glm.hpp"
#include "physics2D/phsyics.h"

class game_object_t;
class scene_t
{
	friend void game_engine::run();
	friend class game_object_t;
	friend class phsyics2D_system;
public:
	scene_t();
	virtual ~scene_t();

	virtual void on_create() = 0;
		
	game_object_t create_game_object();
	game_object_t create_game_object(const std::string& tag);
	game_object_t get_game_object_by_tag(const std::string& tag);

	glm::f32vec2 to_world_position(const glm::f32vec2& screen_position);
private:
	void render();
	void update();
	void calculate_camera_matrix();
private:
	ecs::registry m_registry;
	ecs::entity_t m_camera_id;

	phsyics2D_system system;
	glm::mat4 m_camera_matrix_cache,
				m_inverse_camera_matrix_cache;
};




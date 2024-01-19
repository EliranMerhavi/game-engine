#pragma once


#include "ecs/registry.h"
#include "game_engine.h"
#include "glm/glm.hpp"
#include "physics2D/phsyics.h"

class game_object_t;
class scene_t
{
	using selected_camera_data_t = struct {
		ecs::entity_t camera_id;
		glm::mat4 camera_matrix_cache,
				  inverse_camera_matrix_cache;
	};

	friend void game_engine::run();
	friend class game_object_t;
	friend class phsyics2D_system;
public:
	scene_t();
	virtual ~scene_t();

	virtual void on_load_resources() = 0;
	virtual void on_create() = 0;

	game_object_t& create_game_object();
	game_object_t& create_game_object(const std::string& tag);
	game_object_t& get_game_object_by_tag(const std::string& tag);
	game_object_t& get_game_object(ecs::entity_t id);

	game_object_t& clone_game_object(ecs::entity_t id);

	void destroy_game_object(const game_object_t& object);

	glm::f32vec2 to_world_position(const glm::f32vec2& screen_position);
private:
	void render_gui();
	void render();
	void update();
	void calculate_camera_matrix();
	
private:


	std::unordered_map<ecs::entity_t, game_object_t> m_game_objects;
	ecs::registry m_registry;
	phsyics2D_system system;
	selected_camera_data_t m_selected_camera_data;
};




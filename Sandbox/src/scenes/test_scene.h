#pragma once

#include "scene/scene_t.h"
#include "resource/resources.h"
#include "scene/components.h"

class test_scene;

using level_loader_t = void(*)(test_scene& scene);
using obstacle_t = enum {
	CIRCLE,
	RECT
};

class test_scene : public scene_t
{
	
public:
	test_scene(level_loader_t level0);
	~test_scene();

	virtual void on_load_resources() override;
	virtual void on_create() override;


	void load_level(level_loader_t loader);
	
	void create_ball(const glm::f32vec2& pos);
	void create_obstacle(obstacle_t type, const glm::f32vec2& pos, const glm::f32vec2& size, const component::rigidBody& rigid_body);
	void create_goal(const glm::f32vec2& pos, const glm::f32vec2& size);
	void clear_level();

private:
	void add_border(const glm::f32vec2& pos, const glm::f32vec2& size);
	void create_animation(const glm::f32vec2& mouse_pos_in_world, const glm::f32vec2& ball_pos);
	
	level_loader_t m_level0;
};
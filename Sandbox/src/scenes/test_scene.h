#pragma once

#include "scene/scene_t.h"
#include "renderer2D/texture_t.h"

class test_scene : public scene_t
{
	using obstacle_t = enum {
		CIRCLE,
		RECT
	};

public:
	test_scene();
	virtual ~test_scene() override;
	virtual void on_create() override;
	
	void create_animation(const glm::f32vec2& mouse_pos_in_world, const glm::f32vec2& ball_pos);

	void create_obstacle(const glm::f32vec2& pos, const glm::f32vec2& size, obstacle_t type, bool is_dynamic, float bounciness);
	void create_ball(const glm::f32vec2& pos);
	void create_goal(const glm::f32vec2& pos, const glm::f32vec2& size);

private:

};
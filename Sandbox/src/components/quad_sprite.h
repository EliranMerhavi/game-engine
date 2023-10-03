#pragma once

#include "game_engine.h"

class quad_sprite : public game_engine::component
{
public:
	quad_sprite(int x, int y, int width, int height);
	virtual void start() override;
	virtual void update(float delta_time) override;
	virtual void destroy() override;
private:
	int x, y, width, height;
	float time_to_change_color;
	glm::f32vec4 color;
};
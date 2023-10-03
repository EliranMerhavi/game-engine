#pragma once

#include "game_engine.h"
#include "../components/quad_sprite.h"

class test_scene : public game_engine::scene
{
public:
	test_scene();
	~test_scene();
	
	virtual void start() override;
	virtual void load_resources() override;
	virtual void render() override;
	virtual void update(float delta_time) override;
	virtual void on_create() override;
private:
	std::vector<quad_sprite> quads;
};
#pragma once

#include "scene/scene.h"

class test_scene : public game_engine::scene
{
public:
	test_scene();
	~test_scene();
	
	virtual void on_create() override;
private:
	uint32_t texture;
};
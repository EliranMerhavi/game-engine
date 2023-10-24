#pragma once

#include "game_engine.h"

#include "renderer2D/orthographic_camera.h"

class test_scene : public game_engine::scene
{
public:
	test_scene();
	~test_scene();
	
	virtual void on_create() override;
private:
	
};
#pragma once

#include "scene/scene.h"

class test_scene : public game_engine::scene
{
public:
	test_scene();
	~test_scene();
	
	virtual void on_create() override;
	void create_texture();
	void create_quad();
private:

	uint32_t tex_id1, tex_id2;
};
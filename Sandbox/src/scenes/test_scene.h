#pragma once

#include "scene/scene_t.h"
#include "renderer2D/texture_t.h"

class test_scene : public scene_t
{
public:
	test_scene();
	virtual ~test_scene() override;
	virtual void on_create() override;
private:
};
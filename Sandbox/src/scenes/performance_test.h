#pragma once
#include "scene/scene_t.h"
#include "glm/glm.hpp"

class performance_test : public scene_t
{
public:
	performance_test();

private:
	void create_object(const glm::f32vec2& pos);
	void on_load_resources() override;
	void on_create() override;

};
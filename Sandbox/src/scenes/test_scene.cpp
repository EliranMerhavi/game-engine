#include "test_scene.h"

#include <iostream>
#include "physics2D/rigidBody.h"
#include "core/time.h"
#include "physics2D/Collisions.h"
#include "scene/game_object.h"
#include "renderer2D/renderer2D.h"
#include "scene/components.h"
#include "glm/gtc/matrix_transform.hpp"

test_scene::test_scene()
{
}

float x = 0, y = 0, degrees = 0.0f;

void test_scene::on_create()
{
	game_engine::game_object camera = create_game_object(), obj = create_game_object();
	
	camera.add<camera_component>(camera_component{ { 0.0f, 500.0f, 500.0f, 0.0f } });
	
	set_primary_camera(camera);

	obj.get<transform_t>().set_position(glm::f32vec2{ 250.0f, 250.0f });
	obj.get<transform_t>().set_scale(glm::f32vec2{ 250, 250 });

	obj.add<renderable_component>([obj] {
		renderer2D::quad(obj.get<transform_t>().transform());
	});

	obj.add<updateable_component>([obj] {
		auto& transform = obj.get<transform_t>();
		transform.set_rotation(fmod(transform.rotation() + time::delta_time(), 360));
	});	
}

test_scene::~test_scene()
{
}



#include "test_scene.h"
#include "renderer2D/renderer2D_utils.h"
#include <iostream>
#include "core/time.h"


test_scene::test_scene() : camera(0.0f, game_engine::application::instance().width(), 0.0f, game_engine::application::instance().height())
{

}

test_scene::~test_scene()
{
}

void test_scene::start()
{
}

void test_scene::load_resources()
{
}

float x = 200, y = 200, degrees = 0;

void test_scene::render()
{	
	camera.set_rotation(degrees);
	renderer2D::set_camera(camera);
	renderer2D::set_color({ 1, 0, 0, 1 });
	renderer2D::circle(250, 250, 250);
	

	// x += 75 * time::delta_time;
	// y += 75 * time::delta_time;
}

void test_scene::update()
{
	camera.set_scale((time::delta_time + 2 * camera.scale()) / 2);
}

void test_scene::on_create()
{
}

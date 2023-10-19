#include "test_scene.h"
#include "renderer2D/renderer2D_utils.h"
#include <iostream>
#include "core/time.h"


test_scene::test_scene() : 
	camera(0.0f, game_engine::application::instance().width(), game_engine::application::instance().height(), 0.0f)
	//camera(0.0f, game_engine::application::instance().width(), game_engine::application::instance().height(), 0.0f)
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
	renderer2D::set_camera(camera);
	renderer2D::set_color({ 1, 0, 0, 1 });
	renderer2D::rotated_quad(250, 250, 250, 250, degrees);
	
	degrees = fmod(degrees + time::delta_time, 360);

	// x += 75 * time::delta_time;
	// y += 75 * time::delta_time;
}

void test_scene::update()
{
}

void test_scene::on_create()
{
}

#include "test_scene.h"
#include "renderer2D/renderer2D_utils.h"
#include <iostream>
#include "physics2D/rigidBody.h"
#include "core/time.h"
#include "physics2D/Collisions.h"



test_scene::test_scene() : 
	camera(0.0f, game_engine::application::instance().width(), game_engine::application::instance().height(), 0.0f)
	//camera(0.0f, game_engine::application::instance().width(), game_engine::application::instance().height(), 0.0f)
{
	for (int i = 1; i >= 1; i--)
		quads.emplace_back(0, 0, i * 100, i * 100);
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

rigidBody C(50, 0, 100, 0, 1, { 200,100 }, { 0,0 }, "square");
rigidBody B(50, 0, 100, 0.01, 1, { 200, 300 }, { 1,0 }, "square");
rigidBody D(50, 1, 50, 0.1, 0.07, { 640, 220 }, { -4, 0 }, "square");



void displayRect(rigidBody A) {
	renderer2D::rotated_quad(A.position.x - sqrt(2) / 2 * A.radius, A.position.y - sqrt(2) / 2 * A.radius, sqrt(2) * A.radius, sqrt(2) * A.radius, (A.angle - 0.7853) * 57.295);
}


bool collided = false;
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

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
rigidBody B(50, 0, 100, 0, 1, { 200, 300 }, { 0,0 }, "square");
rigidBody D(50, 0, 50, 0, 0.07, { 640, 220 }, { -4, 0 }, "square");



void displayRect(rigidBody A) {
	renderer2D::rotated_quad(A.position.x - sqrt(2) / 2 * A.radius, A.position.y - sqrt(2) / 2 * A.radius, sqrt(2) * A.radius, sqrt(2) * A.radius, (A.angle - 0.7853) * 57.295);
}


bool collided = false;
void test_scene::render()
{	
	renderer2D::set_camera(camera);
	displayRect(C);
	displayRect(B);
	displayRect(D);
}

void test_scene::update()
{
	//Always put update first! There should probably be some universal loop that updates before we do any more logic.
	C.updateRect(1);
	B.updateRect(1);
	D.updateRect(1);
	collisions::angularCollision(C, B, 1);
	collisions::angularCollision(D, B, 1);
	collisions::angularCollision(C, D, 1);
	//std::cout << A.omega << ", " << B.omega << "\n";

}

void test_scene::on_create()
{
}

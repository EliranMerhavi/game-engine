#include "test_scene.h"
#include "renderer2D/renderer2D_utils.h"
#include <iostream>
#include "physics2D/rigidBody.h"
#include "core/time.h"
#include "physics2D/Collisions.h"



test_scene::test_scene()
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
	//float angA = (A.angle - 0.7853) * 57.295;
	//float angB = (B.angle - 0.7853) * 57.295;
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
	collisions::angularCollision(C, B,1);
	collisions::angularCollision(B, D, 1);
	collisions::angularCollision(C, D, 1);
	//std::cout << A.omega << ", " << B.omega << "\n";

}

void test_scene::on_create()
{
}

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


void test_scene::render()
{	

}

void test_scene::update()
{

}

void test_scene::on_create()
{
}

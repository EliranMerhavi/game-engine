#include "test_scene.h"

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

void test_scene::render()
{
}

void test_scene::update(float delta_time)
{
	renderer2D::set_color({ 1, 1, 1, 1 });
	renderer2D::draw_quad(0, 0, 200, 200);
	//renderer2D::draw_texture("D:\\programming-stuff\\programming-projects\\visual-studio-projects\\game-engine\\Sandbox\\assets\\images\\container.jpg", 0, 0, 200, 200);
}

void test_scene::on_create()
{
}

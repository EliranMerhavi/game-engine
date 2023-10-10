#include "test_scene.h"
#include "renderer2D/renderer2D_utils.h"
#include <iostream>
#include "core/time.h"


test_scene::test_scene()
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

float x = 0, y = 0;
void test_scene::render()
{
//	renderer2D::set_camera(glm::ortho(0.0f, (float)m_window.width(), (float)m_window.height(), 0.0f, -1.0f, 1.0f));
	
	renderer2D::draw_quad(x, y, 20, 20);

	x += 75 * time::delta_time;
	y += 75 * time::delta_time;
}

void test_scene::update()
{
	
}

void test_scene::on_create()
{
}

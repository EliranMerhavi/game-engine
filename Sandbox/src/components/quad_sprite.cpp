#include "quad_sprite.h"
#include <iostream>

quad_sprite::quad_sprite(int x, int y, int width, int height)
	: x(x), y(y), width(width), height(height), time_to_change_color{0}, color{1.0f / (rand() % 255),1.0f / (rand() % 255),1.0f / (rand() % 255), 1}
{
}

void quad_sprite::start()
{
}

void quad_sprite::update(float delta_time)
{
	renderer2D::set_color(color);
	renderer2D::quad(x, y, width, height);

	if (time_to_change_color >= 1)
	{
		color = { 1.0f / (rand() % 255),1.0f / (rand() % 255),1.0f / (rand() % 255), 1 };	
		time_to_change_color = 0;
	}
	time_to_change_color += delta_time;
}

void quad_sprite::destroy()
{
}

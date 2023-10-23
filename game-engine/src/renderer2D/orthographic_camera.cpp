#include "pch.h"
#include "orthographic_camera.h"

game_engine::orthographic_camera::orthographic_camera(float left, float right, float bottom, float top) :
	m_projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_view(1.0f), m_cache(1.0f), 
	m_position(0.0f), 
	m_rotation(0.0f)
{
	update();
}

const glm::f32vec2& game_engine::orthographic_camera::position() const
{
	return m_position;	
}

void game_engine::orthographic_camera::set_position(const glm::f32vec3& position)
{
	m_position = position;
	update();	
}

float game_engine::orthographic_camera::rotation() const
{
	return m_rotation; 
}

void game_engine::orthographic_camera::set_rotation(float rotation)
{
	m_rotation = rotation;
	update();
}

void game_engine::orthographic_camera::update()
{
	glm::mat4 transform(1.0f);

	transform = glm::translate(transform, m_position);
	transform = glm::rotate(transform, glm::radians(m_rotation), glm::f32vec3(0.0f, 0.0f, 1.0f));

	m_view = glm::inverse(transform);
	m_cache = m_projection * m_view;
}

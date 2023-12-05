#include "pch.h"
#include "collider_callback.h"

component::collider_callback::collider_callback(game_engine::game_object obj, const collider_function& callback) 
	: m_callback(callback), m_obj(obj)
{
}

void component::collider_callback::on_collision(game_engine::game_object& other) const
{
	m_callback(m_obj, other);
}

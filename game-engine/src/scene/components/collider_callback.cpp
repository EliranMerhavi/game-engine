#include "pch.h"
#include "collider_callback.h"

component::collider_callback::collider_callback(const collider_function& callback) 
	: m_callback(callback)
{
}

void component::collider_callback::on_collision(game_engine::game_object&  obj, game_engine::game_object& other) const
{
	m_callback(obj, other);
}

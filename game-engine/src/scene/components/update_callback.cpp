#include "pch.h"
#include "update_callback.h"


component::update_callback::update_callback(game_object_t obj, const update_function& callback) :
	m_callback(callback), m_obj(obj)
{
}

void component::update_callback::update() const
{
	m_callback(m_obj);
}

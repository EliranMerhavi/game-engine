#include "pch.h"
#include "render_callback.h"


component::render_callback::render_callback(game_object_t obj, const render_function& callback) :
	m_callback(callback), m_obj(obj)
{
}

void component::render_callback::render() const
{
	m_callback(m_obj);
}

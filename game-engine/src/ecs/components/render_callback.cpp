#include "pch.h"
#include "render_callback.h"

component::render_callback::render_callback(const render_function& callback) : m_callback(callback)
{
}

void component::render_callback::render()
{
	m_callback();
}

#include "pch.h"
#include "update_callback.h"

component::update_callback::update_callback(const update_function& callback) : m_callback(callback)
{
}

void component::update_callback::update() const
{
	m_callback();
}

#include "pch.h"
#include "components.h"

updateable_component::updateable_component(const update_function& func) : m_func(func)
{

}

void updateable_component::update()
{
	this->m_func();
}

renderable_component::renderable_component(const render_function& func) : m_func(func)
{

}

void renderable_component::render()
{
	this->m_func();
}


camera_component::camera_component(const game_engine::orthographic_camera& camera) : m_camera(camera)
{
}

tag_component::tag_component(const std::string& tag) : m_tag(tag)
{
}
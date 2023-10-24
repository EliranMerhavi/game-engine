#pragma once
#include "glm/glm.hpp"
#include "entt/entt.hpp"
#include "renderer2D/orthographic_camera.h"
#include "transform_t.h"


class updateable_component
{
public:
	using update_function = std::function<void()>;
	updateable_component(const updateable_component&) = default;
	updateable_component(const update_function& func);
	void update();
private:
	update_function m_func;
};

class renderable_component
{
public:
	using render_function = std::function<void()>;
	renderable_component(const renderable_component&) = default;
	renderable_component(const render_function& func);
	void render();
private:
	render_function  m_func;
};

class camera_component
{
public:
	camera_component() = default;
	camera_component(const camera_component&) = default;
	camera_component(const game_engine::orthographic_camera& camera);

	game_engine::orthographic_camera& camera() { return m_camera; }
	const game_engine::orthographic_camera& camera() const { return m_camera; }
private:
	game_engine::orthographic_camera m_camera;
};


class tag_component
{
	tag_component() = default;
	tag_component(const tag_component&) = default;
	tag_component(const std::string& tag);

	const std::string& tag() const { return m_tag; }
private:
	const std::string m_tag;
};
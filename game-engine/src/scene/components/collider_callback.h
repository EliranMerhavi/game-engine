#pragma once

#include "scene/game_object_t.h"

namespace component
{
	class collider_callback
	{
		using collider_function = void(*)(game_object_t& obj, game_object_t& collided);
	public:
		collider_callback() = default;
		collider_callback(const collider_callback& other) = default;
		collider_callback(const collider_function& callback);
		void on_collision(game_object_t& obj, game_object_t& other) const;
	private:
		collider_function m_callback;
	};
}
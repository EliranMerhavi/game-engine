#pragma once

#include "scene/game_object.h"

namespace component
{
	class collider_callback
	{
		using collider_function = void(*)(game_engine::game_object& obj, game_engine::game_object& collided);
	public:
		collider_callback(game_engine::game_object obj, const collider_function& callback);
		void on_collision(game_engine::game_object& other) const;
	private:
		collider_function m_callback;
		mutable game_engine::game_object m_obj;
	};
}
#pragma once
#include <functional>
#include "core/time.h"
#include "scene/game_object.h"

namespace component
{
	class update_callback
	{
	public:
		using update_function = void(*)(game_engine::game_object& obj);
		update_callback(game_engine::game_object obj, const update_function& callback);
		void update() const;
	private:
		update_function m_callback;
		mutable game_engine::game_object m_obj;
	};
}
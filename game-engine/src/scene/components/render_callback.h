#pragma once
#include <functional>
#include "core/time.h"
#include "scene/game_object.h"

namespace component
{
	class render_callback
	{
	public:
		using render_function = void(*)(game_engine::game_object& obj);
		render_callback(game_engine::game_object obj, const render_function& callback);
		void render() const;
	private:
		render_function m_callback;
		mutable game_engine::game_object m_obj;
	};
}
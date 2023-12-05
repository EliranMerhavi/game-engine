#pragma once
#include <functional>
#include "core/time.h"
#include "scene/game_object_t.h"

namespace component
{
	class render_callback
	{
	public:
		using render_function = void(*)(game_object_t& obj);
		render_callback(game_object_t obj, const render_function& callback);
		void render() const;
	private:
		render_function m_callback;
		mutable game_object_t m_obj;
	};
}
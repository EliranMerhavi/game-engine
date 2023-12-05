#pragma once
#include <functional>
#include "core/time.h"
#include "scene/game_object_t.h"

namespace component
{
	class update_callback
	{
	public:
		using update_function = void(*)(game_object_t& obj);
		update_callback(game_object_t obj, const update_function& callback);
		void update() const;
	private:
		update_function m_callback;
		mutable game_object_t m_obj;
	};
}
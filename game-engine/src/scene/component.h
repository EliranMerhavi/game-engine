#pragma once

#include "game_object.h"

namespace game_engine
{
	class component
	{
	public:
		component();

		virtual void start() = 0;
		virtual void update(float delta_time) = 0;
		virtual void destroy() = 0;

		id_t id();
	private:
		id_t m_id;
		static int64_t s_id_counter;
	};
}

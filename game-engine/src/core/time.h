#pragma once

#include "config.h"

namespace game_engine
{
	void run(const config_t& config);
}

struct time
{
	static float delta_time() { return s_delta_time; }
private:
	static float s_delta_time;
	friend void game_engine::run(const config_t& config);
};
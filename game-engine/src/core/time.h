#pragma once

#include "game_engine.h"

struct time
{
	static float delta_time() { return s_delta_time; }
private:
	static float s_delta_time;
	friend void game_engine::run();
};
#pragma once

#include "game_engine.h"


using time_step_t = float;

struct time
{
	static time_step_t delta_time(){ return s_delta_time; }
	static time_step_t current();
private:
	static time_step_t s_delta_time;
	friend void game_engine::run();
};
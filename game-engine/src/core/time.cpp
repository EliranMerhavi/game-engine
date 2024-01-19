#include"pch.h"
#include "time.h"

float time::s_delta_time = 0.0f;

time_step_t time::current()
{
	return glfwGetTime() * 1000;
}
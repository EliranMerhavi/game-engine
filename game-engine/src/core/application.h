#pragma once

#include "window.h"
#include "scene/scene.h"
#include <chrono>

namespace game_engine
{
	class application
	{
		using time_point = std::chrono::steady_clock::time_point;
	private:
		application();
	public:
		void run();
		void close();
		void on_window_close();
		void set_current_scene(scene& scene);

		static application& instance();
	private:
		window m_window;
		scene* m_current_scene;
		bool m_running;
		time_point m_previous_time;
	};
}
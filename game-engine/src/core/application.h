#pragma once

#include "window.h"
#include "scene/scene.h"
#include <chrono>

namespace game_engine
{
	class application
	{
		using time_point = double;
	private:
		application();
	public:
		void run();
		void close();
		void on_window_close();
		void set_current_scene(scene& scene);
		void set_vsync(bool val);


		static application& instance();
	private:

		window m_window;
		scene* m_current_scene;
		bool m_running;
		
	};
}
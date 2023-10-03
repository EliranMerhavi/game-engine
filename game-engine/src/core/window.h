#pragma once

#include "scene/scene.h"
#include <cstdint>
#include "GLFW/glfw3.h"


namespace game_engine
{
	
	class window 
	{
	public:
		window(uint32_t width, uint32_t height, const char* window_title);
		~window();
		void update();

		uint32_t width() const;
		uint32_t height() const;

	private:
		uint32_t m_width;
		uint32_t m_height;
		GLFWwindow* m_glfw_window;
		scene* m_current_scene;

		static bool s_glfw_initialized;
		static bool s_glew_initialized;
	};
}
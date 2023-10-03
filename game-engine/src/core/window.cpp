#include "pch.h"
#include "window.h"
#include "renderer2D/opengl_debug.h"
#include "renderer2D/renderer2D.h"
#include "application.h"

namespace game_engine
{
	bool window::s_glfw_initialized = false;
	bool window::s_glew_initialized = false;

	window::window(uint32_t width, uint32_t height, const char* window_title)
		:
		m_width(width),
		m_height(height),
		m_glfw_window(nullptr),
		m_current_scene(nullptr)
	{
		if (!s_glfw_initialized)
		{
			if (!glfwInit())
				throw errors::library_init_error(errors::library_enum::GLFW, "error when calling glfwInit()");
			s_glfw_initialized = true;
		}

		m_glfw_window = glfwCreateWindow(width, height, window_title, nullptr, nullptr);

		if (!m_glfw_window)
			throw std::exception("error on glfwCreateWindow()");

		glfwMakeContextCurrent(m_glfw_window);

		if (!s_glew_initialized)
		{
			GLenum error = glewInit();
			if (error != GLEW_OK)
				throw errors::library_init_error(errors::library_enum::GLEW, "error when calling glewInit()\nerror message: " + std::string((const char*)glewGetErrorString(error)));

#ifdef _DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback(opengl::debug::MessageCallBack, 0);
#endif
			s_glew_initialized = true;
		}

		glfwSetWindowCloseCallback(m_glfw_window, [](GLFWwindow* window) {
			application::instance().on_window_close();
		});
	}

	window::~window()
	{
		glfwTerminate();
	}

	void window::update()
	{
		glfwSwapBuffers(m_glfw_window);
		glfwPollEvents();
	}

	uint32_t window::width() const
	{
		return m_width;
	}

	uint32_t window::height() const
	{
		return m_height;
	}
}
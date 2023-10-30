#pragma once
#include <functional>
#include "renderer2D/renderer2D.h"

namespace component
{
	class render_callback
	{
	public:
		using render_function = std::function<void()>;
		render_callback(const render_function& callback);
		void render();
	private:
		render_function m_callback;
	};
}

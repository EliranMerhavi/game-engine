#pragma once
#include <functional>
#include "core/time.h"

namespace component
{
	class update_callback
	{
	public:
		using update_function = std::function<void()>;
		update_callback(const update_function& callback);
		void update() const;
	private:
		update_function m_callback;
	};
}
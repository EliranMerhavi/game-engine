#pragma once
#include <functional>
#include "core/time.h"
#include "scene/game_object_t.h"

namespace component
{
	using update_callback = void(*)(game_object_t& obj);
}
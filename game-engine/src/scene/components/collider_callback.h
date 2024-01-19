#pragma once

#include "scene/game_object_t.h"

namespace component
{
	using collider_callback = void(*)(game_object_t& obj, game_object_t& collided);
}
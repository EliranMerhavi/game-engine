#pragma once

#include "key.h"
#include "GLFW/glfw3.h"

namespace input
{
	key_state get_key_state(keycode_t code);
}

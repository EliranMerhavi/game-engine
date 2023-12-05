#pragma once

#include "codes.h"
#include "glm/glm.hpp"

namespace input
{
	enum state
	{
		RELEASED,
		PRESSED,
		REPEAT
	};

	void init();

	state get_key_state(keycode_t code);
	state get_mouse_state(mousecode_t button);
	float get_mouse_scroll_offset();
	glm::f32vec2 get_mouse_position();
}

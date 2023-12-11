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

	state key_state(keycode_t code);
	state mouse_state(mousecode_t button);
	float mouse_scroll_offset();
	glm::f32vec2 mouse_position();
}

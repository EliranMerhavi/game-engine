#pragma once

#include <stdint.h>

namespace renderer2D
{
	namespace utils
	{
		uint32_t load_texture(const char* filepath, bool flip_verticaly=false);
	}
}

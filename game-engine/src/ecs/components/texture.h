#pragma once

#include <stdint.h>
#include <string>

namespace component
{
	class texture
	{
	public:
		texture() = delete;
		texture(const std::string& filepath, bool flip_verticaly=false);

		uint32_t id() const;
	private:
		uint32_t m_texture_id;
	};
}

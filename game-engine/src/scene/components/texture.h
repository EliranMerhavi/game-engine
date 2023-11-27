#pragma once

#include <string>
#include <array>
#include "glm/glm.hpp"

namespace component
{
	class texture
	{
	public:
		texture() = default;
		texture(const std::string& filepath, bool flip_verticaly=false);
		texture(uint32_t tex_id, const glm::f32vec2& sub_texture_size, const glm::f32vec2& indices, const glm::f32vec2& texture_size);
		texture(uint32_t tex_id);

		uint32_t id() const;
		const std::array<glm::f32vec2, 4>& coords() const;
	private:
		uint32_t m_texture_id;
		std::array<glm::f32vec2, 4> m_coords;
	};
}

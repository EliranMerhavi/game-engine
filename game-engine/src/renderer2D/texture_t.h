#pragma once

#include <stdint.h>
#include <string>
#include "glm/glm.hpp"
#include <array>
#include <iostream>

namespace renderer2D
{
	using texture_coords_t = std::array<glm::f32vec2, 4>;
	void init();

	class texture_t
	{
	public:
		texture_t();
		texture_t(const std::string& filepath, bool flip_verticaly = false);
		~texture_t();

		texture_t& operator=(const texture_t& other);


		uint32_t id() const;
		const glm::f32vec2& dimensions() const;
		const texture_coords_t& coords() const;

		texture_t sub_texture(const glm::f32vec2& start, const glm::f32vec2& sub_texture_dimenions);
		
		void delete_texture();
		bool is_deleted() const;
		bool is_parent() const;
	private:
		texture_t(uint32_t texture_id, glm::f32vec2 dimensions, const texture_coords_t& coords, bool* is_deleted);
		uint32_t m_renderer_id;
		glm::f32vec2 m_dimensions;
		texture_coords_t m_coords;
		mutable bool m_is_parent;
		bool *m_is_deleted;
		friend void renderer2D::init();
	};

}

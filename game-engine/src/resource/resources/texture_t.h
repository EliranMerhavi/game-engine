#pragma once
#pragma once

#include <stdint.h>
#include <string>
#include "glm/glm.hpp"
#include <array>
#include "../resource_t.h"

namespace renderer2D
{
	using texture_coords_t = std::array<glm::f32vec2, 4>;
	void init();
}

namespace resource
{
	class texture_t : public resource_t
	{
		using parent_data_t = struct {
			bool is_deleted;
			bool flip_verticaly;
		};
	public:
		texture_t();
		texture_t(bool flip_verticaly);
		~texture_t();

		void load(const load_args_t& args) override;

		texture_t& operator=(const texture_t& other);


		uint32_t id() const;
		const glm::f32vec2& dimensions() const;
		const renderer2D::texture_coords_t& coords() const;

		texture_t sub_texture(const glm::f32vec2& start, const glm::f32vec2& sub_texture_dimenions);

		void delete_texture();
		bool is_deleted() const;
		bool is_parent() const;
	private:
		texture_t(uint32_t texture_id, glm::f32vec2 dimensions, const renderer2D::texture_coords_t& coords, parent_data_t* parent_data);
		uint32_t m_renderer_id;
		glm::f32vec2 m_dimensions;
		renderer2D::texture_coords_t m_coords;
		mutable bool m_is_parent;
		parent_data_t* m_parent_data;

		friend void renderer2D::init();
	};

}

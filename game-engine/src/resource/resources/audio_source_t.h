#pragma once

#include "../resource_t.h"

namespace resource
{
	class audio_source_t : public resource_t
	{
	public:
		audio_source_t();
		~audio_source_t();
		void load(const load_args_t& args) override;
		uint32_t source_id() const;
	private:
		uint32_t m_buffer_id;
		uint32_t m_source_id;
		
		float m_pitch = 1.0f;
		float m_gain = 1.0f;
		float m_position[3] = { 0, 0, 0 };
		float m_velocity[3] = { 0, 0, 0 };
		bool  m_loop_sound = false;
	};

}
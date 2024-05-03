#pragma once

#include "resource/resources/audio_source_t.h"

namespace audio
{
	void init();
	void shutdown();

	void play(const resource::audio_source_t& audio_resource);
	void play(const resource::audio_source_t& audio_resource, int seconds);

	int state(const resource::audio_source_t& audio_resource);
}
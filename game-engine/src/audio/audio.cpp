#include "pch.h"
#include "audio.h"

#include <assert.h>
#include "util/thread_pool/thread_pool.h"

#define DEFAULT nullptr 

namespace audio
{
	namespace
	{
		ALCdevice* s_alc_device;
		ALCcontext* s_alc_context;
	}
}

void audio::init()
{
	s_alc_device = alcOpenDevice(DEFAULT);
	assert(s_alc_device && "alcOpenDevice(DEFAULT) error");
	s_alc_context = alcCreateContext(s_alc_device, nullptr);
	assert(s_alc_context && "alcCreateContext(s_alc_device, nullptr) error");
	assert(alcMakeContextCurrent(s_alc_context) && "alcMakeContextCurrent(s_alc_context) error");
}

void audio::shutdown()
{
	assert(alcMakeContextCurrent(DEFAULT) && "alcMakeContextCurrent(DEFAULT) error");

	alcDestroyContext(s_alc_context);
	
	assert(s_alc_context && "alcDestroyContext(s_alc_context) error");
	assert(alcCloseDevice(s_alc_device));
}

void audio::play(const resource::audio_source_t& audio_resource)
{
	audio::play(audio_resource, 0);
}

void audio::play(const resource::audio_source_t& audio_resource, int seconds)
{
	if (audio::state(audio_resource) == AL_PLAYING) {
		return;
	}

	alSourcePlay(audio_resource.source_id());
	thread_pool::push(create_wait_for_audio_resource_job(audio_resource));
}

int audio::state(const resource::audio_source_t& audio_resource)
{
	int source = audio_resource.source_id(),
		state;

	alGetSourcei(source, AL_SOURCE_STATE, &state);

	return state;
}
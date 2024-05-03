#include "pch.h"
#include "jobs.h"

#include "util/thread_pool/thread_pool.h"
#include "thread_pool.h"
#include <assert.h>
#include "OpenAL/al.h"

job_t create_wait_for_audio_resource_job(const resource::audio_source_t& audio_resource)
{	
	return [&audio_resource](std::mutex& mutex) {
		while (audio::state(audio_resource) == AL_PLAYING && alGetError() == AL_NO_ERROR)
			;			
	};
}

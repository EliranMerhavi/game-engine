#pragma once

#include "audio/audio.h"
#include <functional>
#include <mutex>

using job_t = std::function<void(std::mutex&)>;

job_t create_wait_for_audio_resource_job(const resource::audio_source_t& audio_resource);
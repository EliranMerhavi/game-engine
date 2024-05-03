#include "pch.h"

#include "audio_source_t.h"
#include "sndfile/sndfile.h"
#include "OpenAL/al.h"


resource::audio_source_t::audio_source_t() : m_buffer_id(0), m_source_id(0)
{
	alGenSources(1, &m_source_id);
	alSourcef(m_source_id, AL_PITCH, m_pitch);
	alSourcef(m_source_id, AL_GAIN, m_gain);
	alSource3f(m_source_id, AL_POSITION, m_position[0], m_position[1], m_position[2]);
	alSource3f(m_source_id, AL_VELOCITY, m_velocity[0], m_velocity[1], m_velocity[2]);
	alSourcei(m_source_id, AL_LOOPING, m_loop_sound);
	//alSourcei(m_source_id, AL_BUFFER, m_buffer_id);
}

resource::audio_source_t::~audio_source_t()
{
	alDeleteSources(1, &m_source_id);
	alDeleteBuffers(1, &m_buffer_id);
}

void resource::audio_source_t::load(const load_args_t& args)
{
	const auto& [filename, file_data, file_size] = args;
	
	ALenum err, format;
	ALuint buffer;
	SNDFILE* sndfile;
	SF_INFO sfinfo;
	short* membuf;
	sf_count_t num_frames;
	ALsizei num_bytes;
	
	sndfile = sf_open(filename.c_str(), SFM_READ, &sfinfo);
	
	assert(sndfile && "sf_open() error");
	assert(sfinfo.frames >= 1 && sfinfo.frames <= (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels && "invalid sfinfo");
	
	format =
		(sfinfo.channels == 1) * AL_FORMAT_MONO16 +
		(sfinfo.channels == 2) * AL_FORMAT_STEREO16;
	
	assert(format && "unsupported channel count");
	
	membuf = new short[sfinfo.frames * sfinfo.channels];

	num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
	
	assert(num_frames >= 1 && "sf_readf_short()");
	
	num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

	buffer = 0;

	alGenBuffers(1, &buffer);
	
	alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

	delete membuf;
	sf_close(sndfile);
	
	assert(num_frames >= 1 && "failed to read samples");
	
	assert(alGetError() == AL_NO_ERROR && "OpenAL error");

	m_buffer_id = buffer;
	alSourcei(m_source_id, AL_BUFFER, m_buffer_id);
}

uint32_t resource::audio_source_t::source_id() const
{
	return m_source_id;
}

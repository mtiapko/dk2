#ifndef __DK_AUDIO_SOUND_H__
#define __DK_AUDIO_SOUND_H__

#include <AL/al.h>
#include "audio/source_data.h"

namespace dk::audio
{

class sound
{
private:
	ALuint m_id;

	static ALenum convert_to_al_fmt(uint32_t num_channels, uint32_t bits_per_sample) noexcept;

public:
	sound() noexcept;
	~sound() noexcept;

	ALuint id() const noexcept { return m_id; }

	status create(const sound_data& data) noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_AUDIO_SOUND_H__

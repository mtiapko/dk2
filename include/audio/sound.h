#ifndef __DK_AUDIO_SOUND_H__
#define __DK_AUDIO_SOUND_H__

#include <AL/al.h>
#include "audio/sound_data.h"

namespace dk::audio
{

class sound final: public resource
{
private:
	ALuint m_id;

	static ALenum convert_to_al_fmt(uint32_t num_channels, uint32_t bits_per_sample) noexcept;

public:
	sound() noexcept;
	~sound() noexcept override;

	ALuint id() const noexcept { return m_id; }

	status create(string_view file_path, sound_data_fmt fmt = sound_data_fmt::AUTO) noexcept;
	status create(const sound_data& data) noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_AUDIO_SOUND_H__

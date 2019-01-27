#ifndef __DK_AUDIO_SOUND_H__
#define __DK_AUDIO_SOUND_H__

#include <AL/al.h>
#include "Status.h"
#include "audio/SoundData.h"

namespace dk::audio
{

class Sound final: public Resource
{
private:
	ALuint m_id;

	static ALenum convert_to_al_fmt(uint32_t num_channels, uint32_t bits_per_sample) noexcept;

public:
	Sound() noexcept;
	~Sound() noexcept override;

	static ResourceType type() noexcept { return ResourceType::SOUND; }

	ALuint id() const noexcept { return m_id; }

	Status create(const SoundData& sound_data) noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_AUDIO_SOUND_H__

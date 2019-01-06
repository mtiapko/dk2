#ifndef __DK_AUDIO_SOURCE_H__
#define __DK_AUDIO_SOURCE_H__

#include "status.h"
#include "audio/sound.h"

namespace dk::audio
{

class source
{
private:
	ALuint m_id;

public:
	source() noexcept;
	~source() noexcept;

	void play() const noexcept;
	void pause() const noexcept;
	void stop() const noexcept;

	void set_sound(const sound& snd) const noexcept;
	void set_pitch(float val) const noexcept;
	void set_gain(float val) const noexcept;
	void set_pos(float x, float y, float z) const noexcept;
	void set_vel(float x, float y, float z) const noexcept;
	void set_loop(bool val) const noexcept;

	status create() noexcept;
};

}

#endif  //  !__DK_AUDIO_SOURCE_H__

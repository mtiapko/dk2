#ifndef __DK_AUDIO_SOURCE_H__
#define __DK_AUDIO_SOURCE_H__

#include "Status.h"
#include "math/Vec.h"
#include "audio/Sound.h"

namespace dk::audio
{

class Source
{
private:
	ALuint m_id;

public:
	Source() noexcept;
	~Source() noexcept;

	void play() const noexcept;
	void pause() const noexcept;
	void rewind() const noexcept;
	void stop() const noexcept;

	float sec_offset() const noexcept;
	int32_t byte_offset() const noexcept;

	void set_sec_offset(float val) const noexcept;
	void set_byte_offset(int32_t val) const noexcept;

	void set(const Sound& snd) const noexcept;
	void remove_sound() const noexcept;

	void set_pitch(float val) const noexcept;
	void set_gain(float val) const noexcept;
	void set_pos(math::Vec3f val) const noexcept;
	void set_dir(math::Vec3f val) const noexcept;
	void set_velocity(math::Vec3f val) const noexcept;
	void set_looping(bool val) const noexcept;

	float pitch() const noexcept;
	float gain() const noexcept;
	math::Vec3f pos() const noexcept;
	math::Vec3f dir() const noexcept;
	math::Vec3f velocity() const noexcept;
	bool looping() const noexcept;

	Status create() noexcept;
	void destroy() noexcept;
};

}

#endif  //  !__DK_AUDIO_SOURCE_H__

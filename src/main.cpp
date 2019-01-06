#include "log.h"
#include "core.h"
#include "audio/core.h"
#include "audio/sound.h"
#include "audio/source.h"

using namespace dk;

int main()
{
	if (auto res = core::create(); !res)
		return res;

	if (auto res = audio::core::create(); !res)
		return res;

	audio::source src;
	if (auto res = src.create(); !res)
		return res;

	audio::sound_data sint_data;
	if (auto res = sint_data.create("res/audio/sint.wav"); !res)
		return res;

	audio::sound sint;
	if (auto res = sint.create(sint_data); !res)
		return res;

	src.set_gain(1.0f);
	src.set_pitch(1.0f);
	src.set_sound(sint);
	src.play();
	if (auto res = core::run(); !res)
		return res;

	return 0;
}

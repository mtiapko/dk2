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

	audio::sound_data wind_data;
	if (auto res = wind_data.create("res/audio/wind.wav"); !res)
		return res;

	audio::sound wind;
	if (auto res = wind.create(wind_data); !res)
		return res;

	src.set_gain(10.0f);
	src.set_pitch(2.0f);
	src.set_sound(wind);
	src.play();
	if (auto res = core::run(); !res)
		return res;

	return 0;
}

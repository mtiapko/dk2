#include "log.h"
#include "mem.h"
#include "fs/file.h"
#include "audio/source_data.h"

namespace dk::audio
{

sound_data::sound_data() noexcept
	: m_data(nullptr)
{}

sound_data::~sound_data() noexcept
{
	if (m_data != nullptr)
		mem::dealloc(m_data);
}

status sound_data::create(string_view file_path, sound_data_fmt fmt /* = sound_data_fmt::AUTO */) noexcept
{
	fmt = sound_data_fmt::WAVE;  //  TODO: you know what to do...
	switch (fmt) {
		case sound_data_fmt::WAVE: return this->load_wave(file_path);
		default:
			DK_LOG_ERROR("Unexpected sound data format");
			return status::ERROR;
	}
}

}

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "dk/os/File.h"
#include "dk/Log.h"

namespace dk::os
{

/* static */ Status File::read(String& data, StringView path) noexcept
{
	File file;
	if (auto err = file.open(path); !err)
		return err;

	size_t size;
	if (auto err = file.size(size); !err)
		return err;

	data.resize(size);
	if (file.read(data.data(), size) != size) {
		DK_LOG_ERROR("Failed to read whole file '", path, '\'');
		return Status::ERROR;
	}

	return Status::OK;
}

Status File::size(size_t& size) const noexcept
{
	struct stat stat;
	if (fstat(m_id, &stat) < 0) {
		DK_LOG_ERROR("Failed to get stat of file '", m_path, "': ", strerror(errno));
		return Status::ERROR;
	}

	size = stat.st_size;
	return Status::OK;
}

size_t File::read(void* data, size_t max_size) noexcept
{
	size_t size = ::read(m_id, data, max_size);
	if (size == (size_t)-1) {
		DK_LOG_ERROR("Failed to read file '", m_path, "': ", strerror(errno));
		return -1;
	}

	return size;
}

Status File::open(StringView path) noexcept
{
	m_path = path;
	m_id = ::open(m_path.data(), O_RDONLY);
	if (m_id == -1) {
		DK_LOG_ERROR("Failed to open file '", path, "': ", strerror(errno));
		return Status::ERROR;
	}

	return Status::OK;
}

Status File::close() noexcept
{
	::close(m_id);
	m_id = 0;

	return Status::OK;
}

}

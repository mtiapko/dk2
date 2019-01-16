#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "Assert.h"
#include "fs/File.h"

namespace dk::fs
{

File::File() noexcept
	: m_id(BAD_ID)
{}

File::~File() noexcept
{
	close();
}

/* static */ Status File::read(StringView path, String& data) noexcept
{
	File file;
	if (auto ret = file.open(path); !ret)
		return ret;

	size_t size;
	if (auto ret = file.size(size); !ret)
		return ret;

	if (size == BAD_SIZE) {
		DK_LOG_ERROR("File '", path, "' has undefined size");
		return Status::ERROR;
	}

	data.resize(size);
	size = file.read(data.data(), data.size());
	if (size == BAD_SIZE)
		return Status::ERROR;

	if (size != data.size()) {
		DK_LOG_ERROR("Failed to read whole file '", path, '\'');
		return Status::ERROR;
	}

	return Status::OK;
}

Status File::open(StringView path) noexcept
{
	/* XXX: if path has wrong value - can be buffer overrun */
	DK_ASSERT(!path.empty() && *(path.data() + path.size()) == '\0');

	m_path = path;
	m_id = ::open(path.data(), O_RDONLY);
	if (m_id == BAD_ID) {
		DK_LOG_ERROR("Failed to open file '", path, "': ", strerror(errno));
		return Status::ERROR;
	}

	return Status::OK;
}

Status File::close() noexcept
{
	if (m_id != BAD_ID && ::close(m_id) < 0) {
		DK_LOG_ERROR("Failed to close file '", m_path, "': ", strerror(errno));
		return Status::ERROR;
	}

	m_id = BAD_ID;
	return Status::OK;
}

Status File::size(size_t& val) const noexcept
{
	struct stat stat;
	if (fstat(m_id, &stat) < 0) {
		DK_LOG_ERROR("Failed to get stat of file '", m_path, "': ", strerror(errno));
		return Status::ERROR;
	}

	val = stat.st_size;
	return Status::OK;
}

Status File::move_cursor(ssize_t offset) const noexcept
{
	if (lseek(m_id, offset, SEEK_CUR) < 0) {
		DK_LOG_ERROR("Failed to move cursor in file '", m_path, "': ", strerror(errno));
		return Status::ERROR;
	}

	return Status::OK;
}

size_t File::read(void* data, size_t max_size) const noexcept
{
	size_t size = ::read(m_id, data, max_size);
	if (size == BAD_SIZE) {
		DK_LOG_ERROR("Failed to read file '", m_path, "': ", strerror(errno));
		return BAD_SIZE;
	}

	return size;
}

}

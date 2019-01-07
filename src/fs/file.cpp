#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "assert.h"
#include "fs/file.h"

namespace dk::fs
{

file::file() noexcept
	: m_id(BAD_ID)
{}

file::~file() noexcept
{
	close();
}

/* static */ status file::read(string_view path, string& data) noexcept
{
	file file;
	if (auto res = file.open(path); !res)
		return res;

	size_t size;
	if (auto res = file.size(size); !res)
		return res;

	if (size == BAD_SIZE) {
		DK_LOG_ERROR("File '", path, "' has undefined size");
		return status::ERROR;
	}

	size = file.read(data.data(), data.size());
	if (size == BAD_SIZE)
		return status::ERROR;

	if (size != data.size()) {
		DK_LOG_ERROR("Failed to read whole file '", path, '\'');
		return status::ERROR;
	}

	return status::OK;
}

status file::open(string_view path) noexcept
{
	/* XXX: if path has wrong value - can be buffer overrun */
	DK_ASSERT(!path.empty() && *(path.data() + path.size()) == '\0');

	m_path = path;
	m_id = ::open(path.data(), O_RDONLY);
	if (m_id == BAD_ID) {
		DK_LOG_ERROR("Failed to open file '", path, "': ", strerror(errno));
		return status::ERROR;
	}

	return status::OK;
}

status file::close() noexcept
{
	if (m_id != BAD_ID && ::close(m_id) < 0) {
		DK_LOG_ERROR("Failed to close file '", m_path, "': ", strerror(errno));
		return status::ERROR;
	}

	m_id = BAD_ID;
	return status::OK;
}

status file::size(size_t& val) const noexcept
{
	struct stat stat;
	if (fstat(m_id, &stat) < 0) {
		DK_LOG_ERROR("Failed to get stat of file '", m_path, "': ", strerror(errno));
		return status::ERROR;
	}

	val = stat.st_size;
	return status::OK;
}

status file::move_cursor(ssize_t offset) const noexcept
{
	if (lseek(m_id, offset, SEEK_CUR) < 0) {
		DK_LOG_ERROR("Failed to move cursor in file '", m_path, "': ", strerror(errno));
		return status::ERROR;
	}

	return status::OK;
}

size_t file::read(void* data, size_t max_size) const noexcept
{
	size_t size = ::read(m_id, data, max_size);
	if (size == BAD_SIZE) {
		DK_LOG_ERROR("Failed to read file '", m_path, "': ", strerror(errno));
		return BAD_SIZE;
	}

	return size;
}

}

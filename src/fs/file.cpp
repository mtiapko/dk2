#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "assert.h"
#include "fs/file.h"

namespace dk::fs
{

file::file() noexcept
	: m_id(-1)
{}

file::~file() noexcept
{
	if (m_id >= 0)
		close(m_id);  //  TODO: write close() method
}

status file::open(string_view path) noexcept
{
	m_path = path;
	return open(path, m_id);
}

status file::read(uint8_t* data, size_t size) const noexcept
{
	if ((size_t)::read(m_id, data, size) != size) {
		DK_LOG_ERROR("Failed to read ", size, " byte(s) from file '", m_path, '\'');
		return status::ERROR;
	}

	return status::OK;
}

status file::size(size_t& size_val) const noexcept
{
	return size(size_val, m_path, m_id);
}

/* static */ status file::open(string_view path, int& id) noexcept
{
	DK_ASSERT(!path.empty() && *(path.data() + path.size()) == '\0');

	id = ::open(path.data(), O_RDONLY);
	if (id < 0) {
		DK_LOG_ERROR("Failed to open file '", path, ": ", strerror(errno));
		return status::ERROR;
	}

	return status::OK;
}

/* static */ status file::read(string& data, const string_view& path, int id) noexcept
{
	size_t size;
	if (auto res = file::size(size, path, id); !res)
		return res;

	data.resize(size);
	if ((size_t)::read(id, data.data(), data.size()) != size) {
		DK_LOG_ERROR("Failed to read file '", path, '\'');
		return status::ERROR;
	}

	return status::OK;
}

/* static */ status file::size(size_t& size_val, const string_view& path, int id) noexcept
{
	struct stat stat;
	if (fstat(id, &stat) < 0) {
		DK_LOG_ERROR("Failed to get stat of file '", path, ": ", strerror(errno));
		return 0;
	}

	if (stat.st_size < 0) {
		DK_LOG_ERROR("Failed to get size of file '", path, '\'');
		return 0;
	}

	size_val = stat.st_size;
	return status::OK;
}

/* static */ status file::read(string& data, string_view path) noexcept
{
	int id;
	if (auto res = open(path, id); !res)
		return res;

	auto res = read(data, path, id);
	::close(id);

	return res;
}

}

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "assert.h"
#include "fs/file.h"

namespace dk::fs
{

status file::read(string_view path, string& data)
{
	DK_ASSERT(!path.empty() && path.back() != '\0');

	int file_id = ::open(path.data(), O_RDONLY);
	if (file_id < 0) {
		DK_LOG_ERROR("Failed to open file '", path, '\'');
		return status::ERROR;
	}

	struct stat file_stat;
	if (fstat(file_id, &file_stat) < 0) {
		DK_LOG_ERROR("Failed to get stat of file '", path, '\'');
		return status::ERROR;
	}

	if (file_stat.st_size < 0) {
		DK_LOG_ERROR("Failed to get size of file '", path, '\'');
		return status::ERROR;
	}

	data.resize(file_stat.st_size);
	if (::read(file_id, data.data(), data.size()) != file_stat.st_size) {
		DK_LOG_ERROR("Failed to read file '", path, '\'');
		return status::ERROR;
	}

	::close(file_id);
	return status::OK;
}

}

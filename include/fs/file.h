#ifndef __DK_FS_FILE_H__
#define __DK_FS_FILE_H__

#include "status.h"
#include "containers/string.h"
#include "containers/string_view.h"

namespace dk::fs
{

class file
{
private:
	int         m_id;
	string_view m_path;

public:
	file() noexcept;
	~file() noexcept;

	static constexpr int    BAD_ID = -1;
	static constexpr size_t BAD_SIZE = (size_t)-1;
	static constexpr size_t END_OF_FILE = 0;

	static status read(string_view path, string& data) noexcept;

	status open(string_view path) noexcept;
	status close() noexcept;

	status size(size_t& val) const noexcept;
	status move_cursor(ssize_t offset) const noexcept;
	size_t read(void* data, size_t max_size) const noexcept;

	template<typename T> size_t read(T& data) const noexcept { return this->read(&data, sizeof(T)); }
};

}

#endif  //  !__DK_FS_FILE_H__

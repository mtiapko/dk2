#ifndef __DK_FS_FILE_H__
#define __DK_FS_FILE_H__

#include "Status.h"
#include "containers/String.h"
#include "containers/StringView.h"

namespace dk::fs
{

class File
{
private:
	int        m_id;
	StringView m_path;

public:
	File() noexcept;
	~File() noexcept;

	static constexpr int    BAD_ID = -1;
	static constexpr size_t BAD_SIZE = (size_t)-1;
	static constexpr size_t END_OF_FILE = 0;

	static Status read(StringView path, String& data) noexcept;

	Status open(StringView path) noexcept;
	Status close() noexcept;

	Status size(size_t& val) const noexcept;
	Status move_cursor(ssize_t offset) const noexcept;
	size_t read(void* data, size_t max_size) const noexcept;

	template<typename T> size_t read(T& data) const noexcept { return this->read(&data, sizeof(T)); }
};

}

#endif  //  !__DK_FS_FILE_H__

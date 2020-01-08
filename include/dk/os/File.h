#ifndef __DK_OS_FILE_H__
#define __DK_OS_FILE_H__

#include "dk/containers/UniquePtr.h"
#include "dk/containers/StringView.h"
#include "dk/containers/String.h"
#include "dk/Status.h"

namespace dk::os
{

class File
{
private:
	String m_path;
	int    m_id = 0;

public:
	~File() noexcept { this->close(); }

	static Status read(String& data, StringView path) noexcept;

	Status size(size_t& size) const noexcept;
	size_t read(void* data, size_t max_size) noexcept;

	Status open(StringView path) noexcept;
	Status close() noexcept;
};

}

#endif // !__DK_OS_FILE_H__

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

	status open(string_view path) noexcept;
	status read(uint8_t* data, size_t size) const noexcept;
	status size(size_t& size_val) const noexcept;

	//  TODO: is it needed: size_t read_to_buff(uint8_t* data, size_t max_size) noexcept; ???

	static status open(string_view path, int& fd) noexcept;
	static status read(string& data, const string_view& path, int id) noexcept;
	static status size(size_t& size_val, const string_view& path, int id) noexcept;

	static status read(string& data, string_view path) noexcept;
};

}

#endif  //  !__DK_FS_FILE_H__

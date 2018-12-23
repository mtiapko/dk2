#ifndef __DK_FS_FILE_H__
#define __DK_FS_FILE_H__

#include "status.h"
#include "storage/string.h"
#include "storage/string_view.h"

namespace dk::fs
{

class file
{
public:
	static status read(string_view path, string& data);
};

}

#endif  //  !__DK_FS_FILE_H__

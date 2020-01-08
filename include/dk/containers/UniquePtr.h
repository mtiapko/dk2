#ifndef __DK_UNIQUE_PTR_H__
#define __DK_UNIQUE_PTR_H__

#include <memory>
#include "dk/Mem.h"

namespace dk
{

template<typename T>
struct dk_default_delete
{
	void operator()(T* t) const noexcept { dk_mem_delete(t); }
};

template<typename T, typename D = dk_default_delete<T>>
using UniquePtr = std::unique_ptr<T, D>;

}

#endif // !__DK_UNIQUE_PTR_H__

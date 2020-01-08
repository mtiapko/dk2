#ifndef __DK_ARRAY_H__
#define __DK_ARRAY_H__

#include <array>

namespace dk
{

template<typename T, size_t Count>
using Array = std::array<T, Count>;

}

#endif // !__DK_ARRAY_H__

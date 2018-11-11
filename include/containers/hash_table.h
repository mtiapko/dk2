#ifndef __DK_HASH_TABLE_H__
#define __DK_HASH_TABLE_H__

#include <unordered_map>

namespace lao
{

template<typename KeyT, typename ValT>
using hash_table = std::unordered_map<KeyT, ValT>;

}

#endif  //  !__DK_HASH_TABLE_H__

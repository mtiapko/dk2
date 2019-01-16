#ifndef __DK_HASH_TABLE_H__
#define __DK_HASH_TABLE_H__

#include <unordered_map>

namespace dk
{

template<typename KeyT, typename ValueT>
using HashTable = std::unordered_map<KeyT, ValueT>;

}

#endif  //  !__DK_HASH_TABLE_H__

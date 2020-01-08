#ifndef __DK_HASH_TABLE_H__
#define __DK_HASH_TABLE_H__

#include <unordered_map>

namespace dk
{

template<
	typename KeyT,
	typename ValueT,
	typename HashT = std::hash<KeyT>,
	typename EqualT = std::equal_to<KeyT>
> using HashTable = std::unordered_map<KeyT, ValueT, HashT, EqualT>;

}

#endif // !__DK_HASH_TABLE_H__

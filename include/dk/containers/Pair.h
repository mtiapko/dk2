#ifndef __DK_PAIR_H__
#define __DK_PAIR_H__

#include <utility>

namespace dk
{

template<typename FirstT, typename SecondT>
using Pair = std::pair<FirstT, SecondT>;

}

#endif // !__DK_PAIR_H__

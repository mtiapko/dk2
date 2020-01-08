#ifndef __DK_UTIL_TYPE_INFO_H__
#define __DK_UTIL_TYPE_INFO_H__

#include <type_traits>

namespace dk::util
{

struct TypeInfo
{

/* is_empty_object */

template<typename T>
struct IsEmptyObject : public T { char dummy; };

template<typename T, std::size_t Size = sizeof(IsEmptyObject<T>)>
struct is_empty_object
{
	static const bool value = std::false_type::value;
};

template<typename T>
struct is_empty_object<T, sizeof(char /* dummy */)>
{
	static const bool value = std::true_type::value;
};

/* short versions */

template<typename T> static constexpr bool is_empty_object_v = is_empty_object<T>::value;

};

}

#endif // !__DK_UTIL_TYPE_INFO_H__

#ifndef ZARATH_KATANA_GENERAL_META_PROGRAMMING_H
#define ZARATH_KATANA_GENERAL_META_PORGRAMMING_H

#include <type_traits>

namespace KaTaNA
{
	namespace General
	{
#define DEF_HAS_(name) \
		template<class T> auto has_##name##_helper(void *) -> decltype(&T::name, std::true_type());\
		template<class T> std::false_type has_##name##_helper(...); \
		template<class T> constexpr bool has_##name(){return std::is_same<std::true_type, decltype(has_##name##_helper<T>(nullptr))>::value;}
	}
}

#endif

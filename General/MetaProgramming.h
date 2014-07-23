#ifndef ZARATH_KATANA_GENERAL_META_PROGRAMMING_H
#define ZARATH_KATANA_GENERAL_META_PORGRAMMING_H

#include <type_traits>

namespace KaTaNA
{
	namespace General
	{
#define DEF_HAS_(name) \
		template<class T> auto has_##name##_helper(T *p) -> decltype(&T::name, std::true_type());\
		template<class T> std::false_type has_##name##_helper(...); \
		template<class T> constexpr bool has_##name(){return decltype(has_##name##_helper<T>(nullptr))::value;}

#define DEF_HAS_EXACT_(name) \
		template<class T, class R, class... ARGS> class has_exact_##name##_struct\
		{\
			template<class X> static std::true_type  check_sig(X);\
			template<class X> static std::false_type check_sig(...);\
			template<class X> static auto            check_exist(void *) -> decltype(check_sig<R (T::*)(ARGS...)>(&X::name));\
			template<class X> static std::false_type check_exist(...);\
		public:\
			const static bool value = decltype(check_exist<T>(nullptr))::value;\
		};\
		template<class T, class R, class... ARGS> constexpr bool has_exact_##name(){return has_exact_##name##_struct<T, R, ARGS...>::value;}
	}
}

#endif

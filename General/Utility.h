#ifndef ZARATH_KATANA_GENERAL_UTILITY_H
#define ZARATH_KATANA_GENERAL_UTILITY_H

#include <utility>

namespace KaTaNA
{
	namespace General
	{
//		template<class T>
//		constexpr const T &Min(const T &x1, const T &x2){return x1 < x2 ? x1 : x2;}
		template<class T>
		constexpr const T &Max(const T &x1, const T &x2){return x1 > x2 ? x1 : x2;}

		template<class T>
		constexpr const T &Min(const T &x0, const T &x1)
		{
			return x0 < x1 ? x0 : x1;
		}
		template<class T, class... Ts>
		constexpr const T &Min(const T &x0, const T &x1, const Ts&... x)
		{
			return x0 < x1 ? Min(x0, x...) : Min(x1, x...);
		}
	}
}

#endif

#ifndef ZARATH_KATANA_GENERAL_RANGE_H
#define ZARATH_KATANA_GENERAL_RANGE_H

#include <cassert>

namespace KaTaNA
{
	namespace General
	{

		template<class T>
		struct Proxy
		{
		protected:
			T &buf;
		public:
			const unsigned int i;

			constexpr Proxy(T &buf, unsigned int i):buf(buf), i(i){}
			operator T&(){return buf;}
			constexpr operator const T&() const{return buf;}
		};

		template<class T>
		constexpr Proxy<T> ProxyMaker(T &buf, unsigned int i){return Proxy<T>(buf, i);}

		template<class T>
		struct Iterator
		{
		protected:
			T &buf;
			unsigned int i;
		public:
			constexpr Iterator(T &buf, unsigned int i):buf(buf),i(i){}
			virtual Iterator &operator++(){++i;return *this;}
			constexpr bool operator!=(const Iterator &ite)const{return i != ite.i;}
			constexpr auto operator*()const -> decltype(ProxyMaker(buf[i], i)){return ProxyMaker(buf[i], i);};
		};

		template<class T>
		class ForallRange
		{
			T &buf;

		public:
			constexpr ForallRange(T &buf):buf(buf){}

			constexpr Iterator<T> begin(){return Iterator<T>(buf, 0);}
			constexpr Iterator<T> end(){return Iterator<T>(buf, buf.N);}

		};

		template<class U>
		constexpr ForallRange<U> Forall(U &buf){return ForallRange<U>(buf);}
	}
}

#endif

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
			T &elem;
		public:
			const unsigned int i;

			constexpr Proxy(T &elem, unsigned int i):elem(elem), i(i){}
			operator T&(){return elem;}
			constexpr operator const T&() const{return elem;}
		};

		template<class T>
		struct Iterator
		{
		protected:
			T &buf;
			unsigned int i;
		public:
			constexpr Iterator(T &buf, unsigned int i):buf(buf),i(i){}
			virtual const Iterator &operator++(){++i;return *this;}
			constexpr bool operator!=(const Iterator &ite)const{return i != ite.i;}
			template<class U>
			static constexpr Proxy<U> ProxyMaker(U &buf, unsigned int i){return Proxy<U>(buf, i);}
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

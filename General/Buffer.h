#ifndef ZARATH_KATANA_GENERAL_BUFFER_H
#define ZARATH_KATANA_GENERAL_BUFFER_H

#include <cassert>

namespace KaTaNA
{
	namespace General
	{
		template<class T>
		class Array
		{
			T *buf;

			struct Iterator
			{
				T *buf;
				unsigned int n;
				Iterator(T *buf, unsigned int n):buf(buf), n(n){}

				T &operator*(){return buf[n];}
				void operator++(){++n;}
				bool operator!=(const Iterator &ite){return n != ite.n;}
			};

			struct ForAll
			{
				T *buf;
				const unsigned int N;
				ForAll(T *buf, unsigned int N):buf(buf), N(N){}

				Iterator begin(){return Iterator(buf, 0);}
				Iterator end(){return Iterator(buf, N);}
			};

		public:
			const unsigned int N;
			ForAll forall;

			Array(unsigned int N):buf(new T[N]), N(N), forall(buf, N){}
			operator T*() const {return buf;}
			T &operator[](unsigned int i){return assert(i < N), buf[i];}
			const T &operator[](unsigned int i) const{return assert(i < N), buf[i];}

		};
	}
}

#endif

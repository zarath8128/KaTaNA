#ifndef ZARATH_KATANA_GENERAL_BUFFER_H
#define ZARATH_KATANA_GENERAL_BUFFER_H

#include <cassert>
#include <iostream>

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

				unsigned int operator*(){return n;}
				void operator++(){++n;}
				bool operator!=(const Iterator &ite){return n != ite.n;}
			};

			struct ForAll
			{
				T *buf;
				const unsigned int N;
				ForAll(T *buf, unsigned int N):buf(buf), N(N){}

				Iterator begin() const {return Iterator(buf, 0);}
				Iterator end() const {return Iterator(buf, N);}
			};

		public:
			const unsigned int N;
			const ForAll forall;

			Array(unsigned int N):buf(new T[N]), N(N), forall(buf, N){}
			~Array(){delete [] buf;}
			Array &operator=(const Array &a)
			{
				assert(N == a.N);
				for(auto i : forall)
					buf[i] = a[i];
				return *this;
			}

			constexpr operator T*() const {return buf;}
			T &operator[](unsigned int i){return assert(i < N), buf[i];}
			const T &operator[](unsigned int i) const{return assert(i < N), buf[i];}

		};

		template<class T>
		std::ostream &operator<<(std::ostream &dest, const Array<T> &a)
		{
			for(auto i : a.forall)
				dest << a[i];
			return dest;
		}
	}
}

#endif

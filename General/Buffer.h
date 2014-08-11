#ifndef ZARATH_KATANA_GENERAL_BUFFER_H
#define ZARATH_KATANA_GENERAL_BUFFER_H

#include <cassert>
#include <iostream>
#include "Range.h"

namespace KaTaNA
{
	namespace General
	{
		template<class T>
		class Array
		{
			T *buf;

		public:
			const unsigned int N;

			Array(unsigned int N):buf(new T[N]), N(N){}//, forall(buf, N){}
			~Array(){delete [] buf;}
			Array &operator=(const Array &a)
			{
				assert(N == a.N);
				for(auto x : Forall(a))
					buf[x.i] = x;
				return *this;
			}

			constexpr operator T*() const {return buf;}
			T &operator[](unsigned int i){return assert(i < N), buf[i];}
			const T &operator[](unsigned int i) const{return assert(i < N), buf[i];}

		};

		template<class T>
		std::ostream &operator<<(std::ostream &dest, const Array<T> &a)
		{
			for(auto x : Forall(a))
				dest << x;
			return dest;
		}
	}
}

#endif

#ifndef ZARATH_KATANA_GENERAL_BUFFER_H
#define ZARATH_KATANA_GENERAL_BUFFER_H

#include <cassert>
#include <iostream>
#include <type_traits>
#include "Range.h"

namespace KaTaNA
{
	namespace General
	{

		template<class T>
		struct IBuffer
		{
			virtual ~IBuffer(){}
			virtual T &operator[](unsigned int i) = 0;
			virtual const T &operator[](unsigned int i) const = 0;
		};

		template<class T>
		class Array
			:public IBuffer<T>
		{
			T *buf;

		public:
			const unsigned int N;

			Array(unsigned int N):buf(new T[N]), N(N){}//, forall(buf, N){}
			Array(const Array &a):Array(a.N)
			{
				*this = a;
			}

			Array(Array &&a):buf(a.buf){a.buf = nullptr;}
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

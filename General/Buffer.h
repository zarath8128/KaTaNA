#ifndef ZARATH_KATANA_GENERAL_BUFFER_H
#define ZARATH_KATANA_GENERAL_BUFFER_H

#include <cassert>
#include <iostream>
#include <type_traits>
#include "Range.h"
#include "Utility.h"
#include "Debug.h"

namespace KaTaNA
{
	namespace General
	{

		template<class T>
		struct IBuffer
		{
			virtual ~IBuffer(){}
			virtual T &operator[](unsigned int i) = 0;
			virtual T operator[](unsigned int i) const = 0;
			virtual unsigned int Size() const = 0;
		};

		template<class T>
		class Array
			:public IBuffer<T>
		{
			T *buf;

		public:
			const unsigned int N;

			Array(unsigned int N):buf(new T[N]), N(N){}
			Array(const Array &a):Array(a.N)
			{
				*this = a;
			}

			Array(Array &&a):buf(a.buf){a.buf = nullptr;}
			~Array(){delete [] buf;}
			Array &operator=(const Array &a)
			{
				ASSERT(N == a.N, "N = %u, a.N = %u", N, a.N);
				for(unsigned int i = 0; i < N; ++i)
					buf[i] = a[i];
				return *this;
			}

			constexpr operator T*() const {return buf;}
			T &operator[](unsigned int i){return ASSERT(i < N, "i = %u, N = %u", i , N), buf[i];}
			T operator[](unsigned int i) const{return ASSERT(i < N, "i = %u, N = %u", i , N), buf[i];}
			unsigned int Size() const {return N;}
		};

		template<bool B, class... T> class print_type;
		template<class... T> class print_type<true, T...>{public:const static bool value = true;};
		template<class... T> class print_type<false, T...>{const static bool value = false;};

		template<class T, class BUFFER = Array<T>>
		class Buffer
			:public IBuffer<T>
		{
			static_assert(print_type<std::is_base_of<IBuffer<T>, BUFFER>::value, BUFFER>::value, "BUFFER must be derived IBuffer");
			IBuffer<T> &buf;
			bool buf_must_be_deleted;
		public:
			const unsigned int offset, N;
			Buffer(unsigned int N)
				:buf(*new BUFFER(N)), buf_must_be_deleted(true), offset(0), N(N){}
			Buffer(unsigned int offset, unsigned int N, IBuffer<T> &buf)
				:buf(buf), buf_must_be_deleted(false), offset(offset), N(N)
			{
				ASSERT(offset + N < buf.Size(), "offset = %u, N = %u, buf.Size() = %u", offset, N, buf.Size());
			}

			T &operator[](unsigned int i){return ASSERT(i < N, "i = %u, N = %u", i, N), buf[offset + i];}
			T operator[](unsigned int i) const{return ASSERT(i < N, "i = %u, N = %u", i, N), buf[offset + i];}
			unsigned int Size() const{return N;}
			unsigned int Next() const{return offset + Next;}
		};

	
/*		template<class T>
		class VLArray
			:public IBuffer<T>
		{
			mutable T *buf;
			unsigned int n;

			void resize(unsigned int new_size)
			{
				T *new_buf = new T[new_size];
				for(unsigned int i = 0; i < Min(N, new_size); ++i)
					new_buf[i] = buf[i];
				delete [] buf;
				buf = new_buf;
			}

		public:
			unsigned int const &N = n;

			T &operator[](unsigned int i)
			{
				if(!(i < N))
					DBG_WRITE("resize %d to %d", N, 2*N), resize(2*N);
				return buf[i];
			}

			const T &operator[](unsigned int i) const
			{
				if(!(i < N))
					DBG_WRITE("resize %d to %d", N, 2*N), resize(2*N);
				return buf[i];
			}
		};
*/
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

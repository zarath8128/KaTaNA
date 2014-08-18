#ifndef ZARATH_KATANA_LA_VECTOR_H
#define ZARATH_KATANA_LA_VECTOR_H

#include <cassert>
#include "../General/Buffer.h"

namespace KaTaNA
{
	namespace LA
	{

		template<class T>
		class IReadableVector
		{
		public:
			virtual T operator[](unsigned int i) const = 0;
		};

		template<class T>
		class IWritableVector
		{
		public:
			virtual T &operator[](unsigned int i) = 0;
		};

		template<class T>
		class IVector
			:public IReadableVector<T>, public IWritableVector<T>
		{};

		template<class T>
		class Vector
			:public virtual IVector<T>
		{
			General::Array<T> &buf;
			const unsigned int offset;
		public:
			const unsigned int N;

			Vector(unsigned int offset, unsigned int N, General::Array<T> &buf):buf(buf), offset(offset), N(N)
			{
				assert(N + offset < buf.N);
			}

			T &operator[](unsigned int i){assert(i < N);return buf[i + offset];}
			T operator[](unsigned int i) const {assert(i < N);return buf[i + offset];}
		};
	}
}

#endif

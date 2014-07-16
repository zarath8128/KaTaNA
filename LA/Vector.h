#ifndef ZARATH_KATANA_LA_VECTOR_H
#define ZARATH_KATANA_LA_VECTOR_H

#include <cassert>

namespace KaTaNA
{
	namespace LA
	{
		template<class T>
		class IVector
		{
		public:
			virtual T &operator[](unsigned int i) = 0;
			constexpr virtual const T &operator[](unsigned int i) const = 0;
			virtual unsigned int dim() = 0;
		};

		template<class T>
		class Vector
			:IVector<T>
		{
			const unsigned int d;
			T *buf;
		public:
			constexpr Vector(unsigned int dim):d(dim), buf(new T[d]){}
			~Vector(){delete [] buf;}
			constexpr T &operator[](unsigned int i){assert(i < d);return buf[i];}
			constexpr const T &operator[](unsigned int i) const {assert(i < d);return buf[i];}
			constexpr unsigned int dim(){return d;}
		};
	}
}

#endif

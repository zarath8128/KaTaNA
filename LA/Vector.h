#ifndef ZARATH_KATANA_LA_VECTOR_H
#define ZARATH_KATANA_LA_VECTOR_H

#include <cassert>
#include <General/Buffer.h>

namespace KaTaNA
{
	namespace LA
	{
		template<class T>
		class IVector
		{
		public:
			virtual T &operator[](unsigned int i) = 0;
			virtual const T &operator[](unsigned int i) const = 0;
			virtual unsigned int dim() const = 0;
		};

		template<class T>
		class Vector
			:public virtual IVector<T>
		{
			const unsigned int d;
			General::Buffer::Array<T> &buf;
		public:
			Vector(unsigned int dim, General::Buffer::Array<T> &buf):d(dim), buf(buf){}
			T &operator[](unsigned int i){assert(i < d);return buf[i];}
			const T &operator[](unsigned int i) const {assert(i < d);return buf[i];}
			unsigned int dim() const {return d;}
		};
	}
}

#endif

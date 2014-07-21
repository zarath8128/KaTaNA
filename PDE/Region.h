#ifndef ZARATH_KATANA_PDE_REGION_H
#define ZARATH_KATANA_PDE_REGION_H

#include <General/Buffer.h>

namespace KaTaNA
{
	namespace PDE
	{

		template<class T>
		class ILine
		{
		public:
			virtual T &operator()(int) = 0;
			const virtual T &operator()(int) const = 0;
		};

		template<class T>
		class Line
			:protected General::Array<T>, public ILine<T>
		{
		public:
			const unsigned int divide, margin;

			Line(unsigned int divide, unsigned int margin):General::Array<T>(divide + 2*margin), divide(divide), margin(margin){}

			T &operator()(int i){return assert(i > -1 - (int)margin && (unsigned int)i < divide + margin), (*this)[i + margin];}
			const T &operator()(int i) const {return assert(i > -1 - (int)margin && (unsigned int)i < divide + margin), (*this)[i + margin];}
		};

		template<class T>
		class FormalLine
			:public ILine<T>
		{
		public:
			const T min, max, dx;
			const unsigned int divide;

			FormalLine(const T &min, const T &max, unsigned int divide):min(min), max(max), dx((max - min)/(divide - 1)), divide(divide){}

			T &operator()(int i){static T dammy; return dammy = min + i*dx;}
			const T &operator()(int i) const {static T dammy; return dammy = min + i*dx;}
		};
	}
}

#endif

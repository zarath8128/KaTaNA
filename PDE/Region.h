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

			T &operator()(int i){return assert(i > -1 - (int)margin), (*this)[i + margin];}
			const T &operator()(int i) const {return assert(i > -1 - (int)margin), (*this)[i + margin];}
		};

		template<class T>
		class UpWind
			:public ILine<T>
		{
			ILine<T> &f, &u;
			T dx;
		public:
			UpWind(ILine<T> &f, ILine<T> &u, const T &dx):f(f), u(u), dx(dx){}

			T &operator()(int i)
			{
				static T dammy;
				return dammy = u(i)*(u(i) > 0 ? f(i) - f(i - 1) : f(i + 1) - f(i))/dx;
			}
			const T &operator()(int i) const
			{
				static T dammy;
				return dammy = u(i)*(u(i) > 0 ? f(i) - f(i - 1) : f(i + 1) - f(i))/dx;
			}
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

		template<class T, class F>
		class FunctionLine
			:public ILine<T>
		{
			mutable F func;
		public:
			FunctionLine(F f):func(f){}

			T &operator()(int i){static T dammy; return dammy = func(i);}
			const T &operator()(int i) const {static T dammy; return dammy = func(i);}
		};

		template<class T, class F>
		FunctionLine<T, F> FuncLineFactory(F func){return FunctionLine<T, F>(func);}

		template<class T>
		class LimitLine
			:public ILine<T>
		{
			ILine<T> &source, &x;
			T min, max, dflt;
		public:
			LimitLine(const T &min, const T &max, ILine<T> &x, ILine<T> &source, const T &dflt = 0):source(source), x(x), min(min), max(max), dflt(dflt){}

			T &operator()(int i){static T dammy; return dammy = x(i) < min || x(i) > max ? dflt : source(i);}
			const T &operator()(int i) const {static T dammy; return dammy = x(i) < min || x(i) > max ? dflt : source(i);}
		};
	}
}

#endif

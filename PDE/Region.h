#ifndef ZARATH_KATANA_PDE_REGION_H
#define ZARATH_KATANA_PDE_REGION_H

#include "../General/Buffer.h"
#include "../General/Debug.h"

namespace KaTaNA
{
	namespace PDE
	{

		template<class T>
		class IReadableLine
		{
		public:
			virtual ~IReadableLine(){}
			virtual T operator()(int) const = 0;
		};

		template<class T>
		class IWritableLine
		{
		public:
			virtual ~IWritableLine(){}
			virtual T &operator()(int)= 0;
		};

		template<class T>
		class Line
			:public IReadableLine<T>, public IWritableLine<T>
		{
			General::IBuffer<T> &buf;
		public:
			const unsigned int offset, length, margin;

			Line(unsigned int offset, unsigned int length, unsigned int margin, General::IBuffer<T> &buffer)
				:Line(offset, length, margin, buffer, [](int i)->T{return 0;}){}
			template<class F>
			Line(unsigned int offset, unsigned int length, unsigned int margin, General::IBuffer<T> &buffer, const F& f)
				:buf(buffer), offset(offset), length(length), margin(margin)
				{
					for(int i = -(int)margin; i < (int)(length + margin); ++i)
						(*this)(i) = f(i);
				}
			~Line(){}

			T &operator()(int i){return assert(-1 - (int)margin < i && i < (int)(length + margin)), buf[i + margin + offset];}
			T operator()(int i) const {return assert(-1 - (int)margin < i && i < (int)(length + margin)), buf[i + margin + offset];}
		};

		template<class T>
		class FormalLine
			:public IReadableLine<T>
		{
		public:
			const T min, max, width;
			const unsigned int N;

			FormalLine(const T &min, const T &max, unsigned int N):min(min), max(max), width((max - min)), N(N){}

			T operator()(int i) const {return min + i*width/(N - 1);}
		};

		template<class T, class F>
		class FunctionLine
			:public IReadableLine<T>
		{
			mutable F func;
		public:
			FunctionLine(F f):func(f){}

			T operator()(int i) const {return func(i);}
		};

		template<class T, class F>
		FunctionLine<T, F> FuncLineFactory(F func){return FunctionLine<T, F>(func);}
	}
}

#endif

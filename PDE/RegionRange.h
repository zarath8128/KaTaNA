#ifndef ZARATH_KATANA_PDE_REGION_RANGE_H
#define ZARATH_KATANA_PDE_REGION_RANGE_H

namespace KaTaNA
{
	namespace PDE
	{
		template<class T>
		struct LineProxy
		{
		protected:
			Line<T> &line;
		public:
			const int i;

			constexpr LineProxy(Line<T> &line, int i):line(line), i(i){}
			operator T&(){return line(i);}
			constexpr operator T&(){return line;}

			T &operator()(int di){return line(i + di);}
			constexpr const T &operator()(int di) const {return line(i + di);}
		};

		template<class T>
		struct LineIterator
		{
		protected:
			Line<T> &line;
			int i;
		public:
			constexpr LineIterator(Line<T> &line, int i):line(line), i(i){}
			virtual const LineIterator &operator++(){++i;return *this;}
			constexpr bool operator!=(const LineIterator &ite) const {return i != ite.i;}
			static constexpr LineProxy<T> ProxyMaker(Line<T> &line, int i){return LineProxy<T>(line, i);}
			LineProxy<T> operator*(){return ProxyMaker(line, i);}
		};

		template<class T>
		struct LineRange
		{
			LineRange(Line<T> &line, int b, int e):line(line), b(b),e(e){}

			constexpr LineIterator<T> begin() const {return LineIterator<T>(line, b);}
			constexpr LineIterator<T> end() const {return LineIterator<T>(line, e);}
		protected:
			Line<T> &line;
			int b, e;
		};

		template<class T>
		LineRange<T> GlobalLineRange(Line<T> &line){return LineRange<T>(line, -(int)line.margin, line.divide + line.margin);}

	}
}

#endif

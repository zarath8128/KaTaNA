#ifndef ZARATH_KATANA_PDE_DIFFERENTIAL_H
#define ZARATH_KATANA_PDE_DIFFERENTIAL_H

#include "Region.h"

namespace KaTaNA
{
	namespace PDE
	{
		template<class T, class F>
		class Differential
			:public IReadableLine<T>
		{
			IReadableLine<T> &u;
			IReadableLine<T> &x;
			mutable F f;
		public:
			Differential(IReadableLine<T> &u, IReadableLine<T> &x, F f):u(u), x(x), f(f){}
			T &operator()(int i){static T dammy; return dammy = f(u, x, i);}
			T operator()(int i) const {return f(u, x, i);}
		};

		template<class T, class F>
		Differential<T, F> DifferentialFactory(IReadableLine<T> &u, IReadableLine<T> &x, F f){return Differential<T, F>(u, x, f);}

		template<class T, class F>
		class FormalDifferential
			:public IReadableLine<T>
		{
			IReadableLine<T> &u;
			T dx_inv;
			mutable F f;
		public:
			FormalDifferential(IReadableLine<T> &u, const T &dx, F f):u(u), dx_inv(1/dx), f(f){}
			T &operator()(int i){static T dammy; return dammy = f(u, dx_inv, i);}
			T operator()(int i) const {return f(u, dx_inv, i);}
		};

		template<class T, class F>
		FormalDifferential<T, F> FormalDifferentialFactory(IReadableLine<T> &u, IReadableLine<T> &x, F f){return Differential<T, F>(u, x, f);}


		template<class T>
		class Forward
			:public IReadableLine<T>
		{
			IReadableLine<T> &u;
			IReadableLine<T> &x;
		public:
			Forward(IReadableLine<T> &u, IReadableLine<T> &x):u(u), x(x){}
			T &operator()(int i)
			{
				static T dammy;
				return dammy = (u(i + 1) - u(i))/(x(i + 1) - x(i));
			}
			T operator()(int i) const
			{
				return (u(i + 1) - u(i))/(x(i + 1) - x(i));
			}
		};

		template<class T>
		class Backward
			:public IReadableLine<T>
		{
			IReadableLine<T> &u;
			IReadableLine<T> &x;
		public:
			Backward(IReadableLine<T> &u, IReadableLine<T> &x):u(u), x(x){}
			T &operator()(int i)
			{
				static T dammy;
				return dammy = (u(i) - u(i - 1))/(x(i) - x(i - 1));
			}
			T operator()(int i) const
			{
				return (u(i) - u(i - 1))/(x(i) - x(i - 1));
			}
		};
	}
}

#endif

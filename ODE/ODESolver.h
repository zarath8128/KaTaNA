#ifndef ZARATH_KATANA_ODE_ODE_SOLBER_H
#define ZARATH_KATANA_ODE_ODE_SOLVER_H

#include "../LA/Vector.h"

namespace KaTaNA
{
	namespace ODE
	{
		template<class T>
		class IODE
		{
		public:
			//independent value    dependent value
			virtual void operator()(const LA::IReadableVector<T> &i_value, LA::IWritableVector<T> &d_value) const= 0;
		};

		template<class T>
		class IODESolver
		{
		public:
			virtual void operator()(const LA::IReadableVector<T> &x0, LA::IWritableVector<T> &x1) = 0;
		};

		template<class T>
		class EulerMethod
		{
			IODE<T> &f;
			T &dt;
			General::IBuffer<T> &buf;
			const unsigned int N;
		public:
			EulerMethod(IODE<T> &func, T &dt, unsigned int N)
				:f(func), dt(dt), buf(*new General::Array<T>(N)), N(N){}
			EulerMethod(IODE<T> &func, T &dt, unsigned int offset, unsigned int N, General::IBuffer<T> &buf)
				:f(func), dt(dt), buf(*new General::SubBuffer<T>(offset, N, buf)), N(N){}
			~EulerMethod(){delete &buf;}

			void operator()(const LA::IReadableVector<T> &x0, LA::IWritableVector<T> &x1)
			{
				
			}
		};
	}
}

#endif

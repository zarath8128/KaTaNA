#ifndef ZARATH_KATANA_VISUALIZE_GPWRAPPER_H
#define ZARATH_KATANA_VISUALIZE_GPWRAPPER_H
#include <cstdarg>
#include <cstdio>
#include <cassert>

#include <PDE/Region.h>

namespace KaTaNA
{
	namespace Visualize
	{

		class GnuPlot
		{
		public:
			GnuPlot(bool isPersist = false):gp(nullptr)
			{
				gp = popen(isPersist?"gnuplot -persist":"gnuplot", "w");
			}
			~GnuPlot()
			{
				pclose(gp);
			}

			template<class T, class U, class RANGE>
			void operator()(const KaTaNA::PDE::ILine<T> &x, const KaTaNA::PDE::ILine<U> &u, const RANGE &range)
			{
				for(auto xi : range)
					(*this)("%f %f\n", x(xi.i), u(xi.i));
				(*this)("e\n");
			}

			void operator()(const char* cmdfmt, ...)
			{
				va_list arg;
				va_start(arg, cmdfmt);
				vfprintf(gp, cmdfmt, arg);
				va_end(arg);
			}

			operator FILE*(){return gp;}

			void flush()
			{
				fflush(gp);
			}
		private:
			FILE *gp;
		};
	}
}
#endif

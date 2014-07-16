#ifndef ZARATH_KATANA_VISUALIZE_GPWRAPPER_H
#define ZARATH_KATANA_VISUALIZE_GPWRAPPER_H
#include <cstdarg>
#include <cstdio>

#include "../LA/Vector.h"
#include <cassert>

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

			void operator()(const KaTaNA::LA::IVector<double> &x, const KaTaNA::LA::IVector<double> &u)
			{
				assert(x.dim() == u.dim());
				for(unsigned int i = 0; i < x.dim(); ++i)
					(*this)("%f %f\n", x[i], u[i]);
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

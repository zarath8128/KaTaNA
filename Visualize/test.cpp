#include <iostream>
#include "GPWrapper.h"
#include <PDE/RegionRange.h>

using namespace KaTaNA::Visualize;
using namespace KaTaNA::PDE;

int main()
{
	GnuPlot gp(true);
	Line<double> u(20, 0);
	FormalLine<double> x(-1, 1, 20);

	//for(int i = 0; i < 20; ++i)
	for(auto xi : GlobalLineRange(u))
		u(xi.i) = 0.2*x(xi.i)*(x(xi.i) - 1);


	gp("plot '-' with line\n");
	gp(x, u, GlobalLineRange(u));

	return 0;
}

#include <iostream>
#include <cmath>
#include "GPWrapper.h"
#include <PDE/RegionRange.h>
#include <General/Sleep.h>

using namespace KaTaNA::Visualize;
using namespace KaTaNA::PDE;
using namespace KaTaNA::General;

int main()
{
	const unsigned int N = 600;
	const double max = 20, min = -1;
	GnuPlot gp(false);
	Line<double> f(N, 1);
	FormalLine<double> x(min, max, N);
	auto u = FuncLineFactory<double>([&x](int i){return 1;});
	auto Sin = FuncLineFactory<double>([&x](int i){return sin(M_PI*(x(i) + 0.5)) + 1;});
	auto Cons = FuncLineFactory<double>([&x](int i){return 2;});
	UpWind<double> ux(f, u, (max - min)/(N - 1));
	const double T = 20, dt = 0.01;
	double t = 0;

	//for(int i = 0; i < 20; ++i)
	for(auto xi : GlobalLineRange(f))
//		f(xi.i) = 0.2*x(xi.i)*(x(xi.i) + 1)*(x(xi.i) - 1);
//		f(xi.i) = LimitLine<double>(-1, 1, x, Sin)(xi.i);
		f(xi.i) = LimitLine<double>(-.5, .5, x, Cons)(xi.i);

	gp("set xr [%f: %f]\n", min, max);
	gp("set yr [%f: %f]\n", -.1, 2.1);

	while(t += dt <= T)
	{
		for(auto xi : CoreLineRange(f))
			xi -= dt*ux(xi.i);
		gp("plot '-' w l, '-' w l\n");
		gp(x, f, GlobalLineRange(f));
		gp(x, u, CoreLineRange(f));
		gp.flush();
		nanosleep(0.01);
	}
	return 0;
}

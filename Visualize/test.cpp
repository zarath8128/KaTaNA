#include <iostream>
#include "GPWrapper.h"

using namespace KaTaNA::Visualize;
using namespace KaTaNA::LA;

int main()
{
	GnuPlot gp(true);
	Vector<double> x(20), u(20);

	for(int i = 0; i < 20; ++i)
		x[i] = i, u[i] = 0.02*i*(i - 19);

	gp("plot '-' with line\n");
	gp(x, u);

	return 0;
}

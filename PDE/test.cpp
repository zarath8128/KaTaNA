#include <iostream>
#include "../General/Buffer.h"
#include "Region.h"
#include "Differential.h"
#include "RegionRange.h"

using namespace KaTaNA::General;
using namespace KaTaNA::PDE;

int main()
{
	const unsigned int N = 200;
	Array<double> buffer(N + 2);
	FormalLine<double> x(-1, 1, N);
	Line<double> u(0, N, 1, buffer, [&](int i){return x(i)*x(i);});
	Forward<double> dudx(u, x);
	auto test = DifferentialFactory(u, x, [](const IReadableLine<double> &u, const IReadableLine<double> &x, int i){return (u(i + 1) - u(i - 1))/(x(i + 1) - x(i - 1));});
	for(int i = 0; i < (int)N; ++i)
		std::cout << x(i) << " " << dudx(i) << " " << test(i) << std::endl;
}

#include "ODESolver.h"
#include <cmath>

using namespace KaTaNA;
using namespace LA;
using namespace ODE;
using namespace General;

class
	:public IODE<double>
{
public:
	void operator()(const IReadableVector<double> &i_val, IWritableVector<double> &d_val) const
	{
		d_val[0] = i_val[1];
		d_val[1] = sin(i_val[0]);
	}
} pendulum;

int main()
{
	double dt = 0.01;
	Array<double> buffer(4);
	EulerMethod<double> euler(pendulum, dt, 1, 2, buffer);
	return 0;
}

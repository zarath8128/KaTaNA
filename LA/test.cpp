#include <iostream>
#include "Vector.h"

using namespace KaTaNA::LA;
using namespace KaTaNA::General;

int main()
{
	Array<double> buffer(20);
	Vector<double> x(0, 10, buffer);
	Vector<double> x2(10, 10, buffer);
	for(unsigned int i = 0; i < 11; ++i)
		x[i] = i;//, x2[i] = i*i;
	for(unsigned int i = 0; i < 20; ++i)
		std::cout << i << ":" << buffer[i] << std::endl;
	return 0;
}

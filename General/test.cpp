#include <iostream>
#include "Buffer.h"
#include "Output.h"
#include "Range.h"
#include <utility>
#include "Sleep.h"
#include "Debug.h"

using namespace KaTaNA::General;

/*class I
	:public IIterator<double>
{
	double *p;
public:
	I(double *p):p(p){}
	I(I &&i):p(i.p){}
	double &operator*(){return *p;}
	IIterator<double> &operator++(){p++; return *this;}

	bool operator!=(const I &i){return p != i.p;}
};

class R
	:public IRange<double>
{
	double *b, *e;
public:
	R(double *array, int length):b(array), e(array + length){}
	const IIterator<double> &begin(){return std::move(I(b));}
	const IIterator<double> &end(){return std::move(I(e));}
};
*/
template<class T>
std::ostream &operator<<(std::ostream &dest, T t){return dest;}
int main()
{
	Array<double> x(20), y(20);
	x[5] = 0.023;
	y = x;
	std::cout << line << y << std::endl;
	DBG_WRITE("test");
	nanosleep(.2);
	DBG_WRITE("test2");
	nanosleep(.4);
	DBG_WRITE();
	std::cout << line << y << std::endl;
	return 0;
}

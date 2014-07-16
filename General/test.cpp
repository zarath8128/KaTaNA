#include <iostream>
#include "Range.h"

using namespace KaTaNA::General;

class I
{
	double *p;
public:
	I(double *p):p(p){}
	double &operator*(){return *p;}
	I &operator++(){p++; return *this;}

	bool operator!=(const I &i){return p != i.p;}
};

class R
	:public IRange<I>
{
	double *b, *e;
public:
	R(double *array, int length):b(array), e(array + length){}
	I begin(){return I(b);}
	I end(){return I(e);}
};

int main()
{
	double x[] = {1, 3, 2, 4, 76, 54, 0};
	R r(x, 7);
	for(auto i : r)
		std::cout << i << std::endl;
	return 0;
}

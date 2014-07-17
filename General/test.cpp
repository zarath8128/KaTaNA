#include <iostream>
#include "Buffer.h"
#include <utility>

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
int main()
{
	double x[] = {1, 3, 2, 4, 76, 54, 0};
//	R r(x, 7);
//	for(auto i : r)
//		std::cout << i << std::endl;
	return 0;
}

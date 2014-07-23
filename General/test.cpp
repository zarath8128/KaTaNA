#include <iostream>
#include "Buffer.h"
#include "Output.h"
#include "Range.h"
#include <utility>
#include "Sleep.h"
#include "Debug.h"
#include <cstring>
#include <cstdio>

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
struct A
{
	void print(){std::cout << "A\n";}
};
struct B
{
	int p;
};
int main()
{

	return 0;
}

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
	void print(int, char){std::cout << "A\n";}
};
struct B
{
	int p;
	int print(char);
};

template<class T>
auto h(void *)->decltype(&T::print, '\0');
template<class T>
int h(...);

int main()
{
//	f(A());
//	f(B());
	std::cout << (sizeof(decltype(h<A>(0))) == sizeof(decltype(h<B>(0)))) << std::endl;
//	check<A>(nullptr);
//	std::cout << CHECK_PRINT<A>().value << std::endl;
//	std::cout << CHECK_PRINT<B>::value << std::endl;
	return 0;
}

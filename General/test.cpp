#include "Debug.h"
#include "Buffer.h"

using namespace KaTaNA::General;

struct A
{
	virtual void say(){std::cout << "Hello A!\n";}
};
struct B
	:public A
{
	void say(){std::cout << "Hello B!\n";}
};

int main()
{
	A aa;
	B bb;
	Clone<A> a(std::move(bb));
	a->say();
	return 0;
}

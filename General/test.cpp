#include <iostream>
#include "Debug.h"
#include "Buffer.h"
#include "Utility.h"

using namespace KaTaNA::General;

struct A
{
	virtual void say(int a = 0){std::cout << "Hello A!\n";
		DBG_WRITE();
		assert(0);
	ASSERT(0);
	}
};
struct B
	:public A
{
	void say(){std::cout << "Hello B!\n";}
};

struct C
{
	~C(){DBG_WRITE("destructed");}
};

const C& f(const C& c)
{
	DBG_WRITE();
	return c;
}

int main()
{
	EXPR_VAL(Min(10, 3, 1, 2));
	Array<double> buffer(20);
//	Buffer<double> buf(10, 5, buffer);
	Buffer<double> buf(10);
//	Buffer<double> pbuf(3, 10, buffer);
//	for(int i = 0; i < 10; ++i)
//		pbuf[i] = i + 20;
//	for(int i = 0; i < 5; ++i)
//		std::cout << i << ":" << buf[i] << std::endl;
//	constexpr const char *name = typeid(Buffer<double>).name();
//	std::cout << typeid(buf).name() << std::endl;
//	assert(0);
//	A().say();
	return 0;
}

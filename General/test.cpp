#include "Debug.h"
int main()
{
	int i = 234;
	DBG_WRITE();
	DBG_WRITE("test");
	DBG_WRITE("%d", 25);
	EXPR_VAL(i); //c++11 only
	return 0;
}

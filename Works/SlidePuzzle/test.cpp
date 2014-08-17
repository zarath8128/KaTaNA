#include <iostream>

int main()
{
	char i;
	while(std::cin >> i)
	{
		std::cout << "i:" << i << "\n";
		while(std::cin.ignore());
	}
	std::cout << "invalid\n";

}

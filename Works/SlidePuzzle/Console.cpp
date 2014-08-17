#include "SlidePuzzle.h"
#include <cstdlib>
#include <ctime>

using namespace Works;

void print_greeting();
SlidePuzzle initialize();
void print_help();

int main()
{
	print_greeting();
	SlidePuzzle s = initialize();

	std::cout << "   ...done!\n";

	while(!s.IsClear())
	{
		std::cout << s;
prompt:
		std::cout << "?:Help  q:Quit  s:Show panel  u:Undo\n";
		std::cout << ">>>";
		char c;
		std::cin >> c;
		switch(c)
		{
			case 'q':
				goto exit;
			case '?':
				print_help();
				goto prompt;
			case 's':
				break;
			case 'u':
				s.Undo();
				break;
			default:
				if(s.Command(c))
					break;
				std::cout << "invalid commnad\n";
				goto prompt;
		}
	}

	std::cout << s;
	std::cout << "Congraturation!\n";

	return 0;

exit:
	std::cout << "quit...\n";
	return 0;
}

void print_greeting()
{
	std::cout <<
		"/==============================\\\n"
		"|=                            =|\n"
		"|=  Slide Puzzle for Console  =|\n"
		"|=                            =|\n"
		"\\==============================/\n";
}

SlidePuzzle initialize()
{
	int mix_level;
	std::cout << "input mix level:";
	std::cin >> mix_level;
	std::cout << "mix level:" << mix_level << "   ...mixing";

	mix_level *= 20;

	char mix_command[mix_level + 1];
	srand(time(0));
	for(int i = 0; i < mix_level; ++i)
		mix_command[i] = []()
			{
				switch(rand() % 4)
				{
					case 0:
						return 'h';
					case 1:
						return 'j';
					case 2:
						return 'k';
					case 3:
						return 'l';
					default:
						return '*';
				}
			}();
	mix_command[mix_level] = '\0';

	return SlidePuzzle(5, 5, mix_command);
}

void print_help()
{
	std::cout << 
		"    k   \n"
		"    ^   \n"
		"h <   > l\n"
		"    v   \n"
		"    j   \n";
		
}

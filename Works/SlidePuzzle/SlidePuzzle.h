#ifndef ZARATH_WORKS_SLIDE_PUZZLE_H
#define ZARATH_WORKS_SLIDE_PUZZLE_H

#include <iostream>
#include <vector>

namespace Works
{
	class State
	{
		int *state;
	public:
		const int row, column;
		State(int row = 5, int column = 5);
		~State();
		int &operator()(int row, int column);
		int operator()(int row, int column) const;
		operator bool() const;
		void FreeSpacePosition(int &row, int &column) const;
	};

	std::ostream &operator<<(std::ostream&, const State&);

	class SlidePuzzle
	{
	friend std::ostream &operator<<(std::ostream&, const SlidePuzzle&);
		State current;
		std::vector<char> initial_command_seq, player_command_seq;
		void Swap(int row1, int column1, int row2, int column2);
		bool RawCommand(char c);
		bool ReverseCommand(char c);
		bool Command(char c, std::vector<char>& v);
	public:
		SlidePuzzle(int row = 5, int column = 5, const char *command_seq = "");
		void FreeSpacePosition(int &row, int &column) const;
		int Row() const;
		int Column() const;
		bool Command(char c);
		void Undo();
		bool IsClear() const;
	};

	std::ostream &operator<<(std::ostream&, const SlidePuzzle&);
}

#endif

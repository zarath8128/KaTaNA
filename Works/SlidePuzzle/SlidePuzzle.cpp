#include "SlidePuzzle.h"
#include <cassert>
#include <iomanip>

namespace Works
{
	State::State(int row, int column)
		:state(new int[row*column]), row(row), column(column)
	{
		for(int i = 0; i < column*row - 1; ++i)
			state[i] = i + 1;
		state[column*row - 1] = 0;
	}

	State::~State()
	{
		delete [] state;
	}

	int &State::operator()(int row, int column)
	{
		assert(0 < row && row <= this->row && 0 < column && column <= this->column);
		return state[(row - 1)*this->column + column - 1];
	}

	int State::operator()(int row, int column) const
	{
		assert(0 < row && row <= this->row && 0 < column && column <= this->column);
		return state[(row - 1)*this->column + column - 1];
	}

	State::operator bool() const
	{
		bool is_clear = true;
		for(int i = 0; i < row*column - 1; ++i)
			is_clear = state[i] == i + 1 ? is_clear : false;
		return is_clear;
	}

	void State::FreeSpacePosition(int &row, int &column) const
	{
		for(int r = 1; r <= this->row; ++r)
			for(int c = 1; c <= this->column; ++c)
				if(!(*this)(r, c))
				{
					row = r, column = c;
					break;
				}
	}

	std::ostream &operator<<(std::ostream &dest, const State& s)
	{
		int digit_width = [](int n)
			{
				int d_width;
				for(d_width = 1; n /= 10; ++d_width);
				return d_width;
			}(s.column*s.row - 1);

		auto print_line = [&dest, &s, digit_width]()
			{
				dest << "+";
				for(int i = 0; i < s.column; ++i)
					dest << std::setw(digit_width + 1) << std::setfill('-') << "+";
				dest << "\n";
			};

		auto print_State_line = [&dest, &s, digit_width](int row)
			{
				int c;
				dest << "|";
				for(int i = 0; i < s.column; ++i)
					if((c = s(row, i + 1)))
						dest << std::setw(digit_width) << std::setfill(' ') << c << "|";
					else
						dest << std::setw(digit_width) << std::setfill(' ') << " " << "|";
				dest << "\n";
			};

		print_line();
		for(int i = 0; i < s.row; ++i)
			print_State_line(i + 1), print_line();

		return dest;
	}

	void SlidePuzzle::Swap(int r1, int c1, int r2, int c2)
	{
		int tmp = current(r2, c2);
		current(r2, c2) = current(r1, c1);
		current(r1, c1) = tmp;
	}

	SlidePuzzle::SlidePuzzle(int row, int column, const char *command_seq)
		:current(row, column)
	{
		while(*command_seq)
			Command(*command_seq++, initial_command_seq);
	}

	void SlidePuzzle::FreeSpacePosition(int &row, int &column) const 
	{
		current.FreeSpacePosition(row, column);
	}

	int SlidePuzzle::Row() const {return current.row;}
	int SlidePuzzle::Column() const {return current.column;}

	bool SlidePuzzle::Command(char c, std::vector<char> &v)
	{
		bool is_valid = RawCommand(c);
		
		if(is_valid)
			v.push_back(c);
		return is_valid;
	}

	bool SlidePuzzle::Command(char c)
	{
		return Command(c, player_command_seq);
	}

	bool SlidePuzzle::RawCommand(char c)
	{
		int row, column;
		FreeSpacePosition(row, column);
		switch(c)
		{
			case 'h':
				if(column == 1)
					return false;
				Swap(row, column, row, column - 1);
				return true;
			case 'j':
				if(row == Row())
					return false;
				Swap(row, column, row + 1, column);
				return true;
			case 'k':
				if(row == 1)
					return false;
				Swap(row, column, row - 1, column);
				return true;
			case 'l':
				if(column == Column())
					return false;
				Swap(row, column, row, column + 1);
				return true;
			default:
				return false;
		}
	}

	bool SlidePuzzle::ReverseCommand(char c)
	{
		switch(c)
		{
			case 'h':
				return RawCommand('l');
			case 'j':
				return RawCommand('k');
			case 'k':
				return RawCommand('j');
			case 'l':
				return RawCommand('h');
			default:
				return false;
		}
	}

	void SlidePuzzle::Undo()
	{
		if(player_command_seq.size())
			ReverseCommand(player_command_seq.back()), player_command_seq.pop_back();
	}

	bool SlidePuzzle::IsClear() const
	{
		return current;
	}

	std::ostream &operator<<(std::ostream &dest, const SlidePuzzle& s)
	{
		dest << s.current;
		int r, c;
		s.FreeSpacePosition(r, c);
		std::cout << "Cur r:" << r << " :" << c << "\n";
		return dest;
	}
}

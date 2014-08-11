#ifndef ZARATH_KATANA_OUTPUT_H
#define ZARATH_KATANA_OUTPUT_H

#include <iostream>

namespace KaTaNA
{
	namespace General
	{
		class LineSeparater
			:public std::ostream
		{
			std::ostream &dest;

		public:
			LineSeparater(std::ostream &dest):dest(dest){}
			LineSeparater(const LineSeparater &ls):std::basic_ios<char>(), std::basic_ostream<char>(), dest(ls.dest){}

			template<class T>
			std::ostream &operator<<(const T& t){return dest << t << "\n", *this;}
		};

		struct LineSeparaterInterface
		{
			LineSeparater operator()(std::ostream &dest){return LineSeparater(dest);}
		};

		static inline LineSeparater operator<<(std::ostream &dest, LineSeparaterInterface lsi)
		{
			return lsi(dest);
		}

		extern LineSeparaterInterface line;
	}
}

#endif

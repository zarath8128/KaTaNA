#ifndef ZARATH_KATANA_GENERAL_RANGE_H
#define ZARATH_KATANA_GENERAL_RANGE_H

#include <cassert>

namespace KaTaNA
{
	namespace General
	{

		template<class T>
		struct IIterator
		{
			virtual IIterator &operator++() = 0;
			template<class U>
			bool operator!=(const U &ite){assert(false && "IIterator::operator!= must be overloaded.");}
			virtual T &operator*() = 0;
		};

		template<class T>
		struct IRange
		{
			virtual const IIterator<T> &begin() = 0;
			virtual const IIterator<T> &end() = 0;
		};
	}
}

#endif

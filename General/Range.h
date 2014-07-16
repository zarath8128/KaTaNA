#ifndef ZARATH_KATANA_GENERAL_CONTAINER_H
#define ZARATH_KATANA_GENERAL_CONTAINER_H

namespace KaTaNA
{
	namespace General
	{
		template<class Ite>
		class IRange
		{
		public:
			virtual Ite begin() = 0;
			virtual Ite end() = 0;
		};
	}
}

#endif

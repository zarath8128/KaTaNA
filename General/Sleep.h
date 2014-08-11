#ifndef ZARATH_KATANA_GENERAL_SLEEP_H
#define ZARATH_KATANA_GENERAL_SLEEP_H

#include <cassert>
#include <ctime>

namespace KaTaNA
{
	namespace General
	{
		static inline void nanosleep(double sec)
		{
			static constexpr unsigned long int nano_scaler = 1'000'000'000;
			timespec tm;
			tm.tv_sec = sec;
			tm.tv_nsec= (sec - tm.tv_sec)*nano_scaler;
			while(nanosleep(&tm, &tm));
		}
	}
}

#endif

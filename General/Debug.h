#ifndef ZARATH_KATANA_GENERAL_DEBUG_H
#define ZARATH_KATANA_GENERAL_DEBUG_H

#ifndef NDEBUG
#define DBG_WRITE(...) do{fprintf(stderr, "file:%s  l:%d  in %s  ", __FILE__, __LINE__, __func__), fprintf(stderr, "msg:"  __VA_ARGS__), fprintf(stderr, "\n");}while(0)
#else
#define DBG_WRITE(...)
#endif

namespace KaTaNA
{
	namespace General
	{




	}
}

#endif

#ifndef ZARATH_KATANA_GENERAL_DEBUG_H
#define ZARATH_KATANA_GENERAL_DEBUG_H

#ifdef __cplusplus
#include <cerrno>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#else
#include <errno.h>
#include <string.h>
#include <stdio.h>
#endif

#ifndef NDEBUG
#define DBG_WRITE(...) fprintf(stderr, "%s:%d In function '%s'", __FILE__, __LINE__, __func__), fprintf(stderr, "  "  __VA_ARGS__), fprintf(stderr, "\n")
#else
#define DBG_WRITE(...)
#endif

#ifndef NDEBUG
#define ERR_CHECK(expr) do{errno = 0; int err_buf; expr; if((err_buf = errno)) DBG_WRITE("%s", strerror(err_buf)); else DBG_WRITE("No error detected");}while(0)
#else
#define ERR_CHECK(expr) do{expr;}while(0)
#endif

#ifdef __cplusplus

namespace KaTaNA
{
	namespace General
	{
		class TypeName
		{
			char * name;
			int status;
		public:
			template<class T>
			TypeName(const T &t):name(abi::__cxa_demangle(typeid(t).name(), 0, 0, &status)){}
			TypeName(const TypeName &t):name((char*)malloc(strlen(t.name) + 1)), status(t.status){strcpy(name, t.name);}
			TypeName(TypeName &&t):name(t.name), status(t.status){t.name = nullptr;}
			TypeName &operator=(const TypeName &t){free(name); name = (char*)malloc(strlen(t.name) + 1); strcpy(name, t.name); status = t.status; return *this;}
			TypeName &operator=(TypeName &&t){free(name); name = t.name; t.name = nullptr; status = t.status; return *this;}
			~TypeName(){free(name);}
			operator const char*(){return name;}
		};

#ifndef NDEBUG
#define EXPR_VAL(expr) std::cerr << __FILE__ << ":" << __LINE__ << " " << TypeName(expr) << " " << #expr << " = " << (expr) << "\n"
#else
#define EXPR_VAL(expr)
#endif

		


		extern "C"
		{
#endif


#ifdef __cplusplus
		}
	}
}
#endif

#endif

#ifndef ZARATH_KATANA_GENERAL_DEBUG_H
#define ZARATH_KATANA_GENERAL_DEBUG_H

#ifdef __cplusplus
#include <cassert>
#include <cerrno>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <utility>
#else
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#endif

//*-----------------------form GNU C Library-----------------------*//
#ifndef __GNUC_PREREQ
#  if defined __GNUC__ && defined __GNUC_MINOR__
#    define __GNUC_PREREQ(maj, min) ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#  else
#    define __GNUC_PREREQ(maj, min) 0
#  endif
#endif

#ifndef __ASSERT_FUNCTION
#  if defined __cplusplus ? __GNUC_PREREQ (2, 6) : __GNUC_PREREQ (2, 4)
#    define __ASSERT_FUNCTION    __PRETTY_FUNCTION__
#  else
#    if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#      define __ASSERT_FUNCTION    __func__
#    else
#      define __ASSERT_FUNCTION    ((__const char *) 0)
#    endif
#  endif
#endif
//*----------------------------------------------------------------*//

#define PRINT_HERE(cstream) fprintf(cstream, "%s:%d: %s: ", __FILE__, __LINE__, __ASSERT_FUNCTION)

#ifndef NDEBUG
#  define ASSERT(expr, ...) {if(!(expr)) PRINT_HERE(stderr), fprintf(stderr, "Assertion `" #expr "' failed. " __VA_ARGS__), fprintf(stderr, "\n"), abort();}while(0);
#else
#  define ASSERT(expr, ...)
#endif

#ifndef NDEBUG
#  define DBG_WRITE(...) PRINT_HERE(stderr), fprintf(stderr, " "  __VA_ARGS__), fprintf(stderr, "\n")
#else
#  define DBG_WRITE(...)
#endif

#ifndef NDEBUG
#  define ERR_CHECK(expr) do{errno = 0; int err_buf; expr; if((err_buf = errno)) DBG_WRITE("%s", strerror(err_buf)); else DBG_WRITE("No error detected");}while(0)
#else
#  define ERR_CHECK(expr) do{expr;}while(0)
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
#define EXPR_VAL(expr) std::cerr << __FILE__ << ":" << __LINE__ << " " << KaTaNA::General::TypeName(expr) << " " << #expr << " = " << (expr) << "\n"
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

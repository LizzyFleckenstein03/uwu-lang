#ifndef _COMMON_STR_H_
#define _COMMON_STR_H_

#include <stdio.h>
#include <stdarg.h>

static inline char *asprintf_wrapper(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	char *ptr;
	vasprintf(&ptr, format, args);
	va_end(args);
	return ptr;
}

#endif

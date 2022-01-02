#ifndef _UWU_COMMON_DIR_H_
#define _UWU_COMMON_DIR_H_

#include <stdlib.h>
#include <libgen.h>
#include <string.h>

static char *wrap_name_func(const char *name, char *(*fn)(char *))
{
	char *copy = strdup(name);
	char *result = fn(copy);
	char *result_copy = strdup(result);

	free(copy);
	return result_copy;
}

static inline char *basename_wrapper(const char *name)
{
	return wrap_name_func(name, &basename);
}

static inline char *dirname_wrapper(const char *name)
{
	return wrap_name_func(name, &dirname);
}

#endif

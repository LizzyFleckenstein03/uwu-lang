#ifndef _LOAD_H_
#define _LOAD_H_

#include <stddef.h>
#include "api/vm.h"

typedef struct
{
	void *api_library;
	UwUVMFunction *main_function;
	UwUVMFunction     **functions;
	size_t          num_functions;
	void     **libraries;
	size_t num_libraries;
} Program;

Program load_program(const char *progname, const char *modname);

#endif

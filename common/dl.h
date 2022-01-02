#ifndef _UWU_COMMON_DL_H_
#define _UWU_COMMON_DL_H_

#include <dlfcn.h>
#include "err.h"

inline static void check_dlerror()
{
	char *err = dlerror();
	if (err)
		error("library error: %s\n", err);
}

#endif

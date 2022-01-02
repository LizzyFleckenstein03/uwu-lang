#ifndef _UWU_COMMON_FILE_H_
#define _UWU_COMMON_FILE_H_

#include <stdio.h>
#include <stdbool.h>

inline static bool file_exists(const char *filename)
{
	FILE *f = fopen(filename, "r");

	if (f) {
		fclose(f);
		return true;
	}

	return false;
}

#endif

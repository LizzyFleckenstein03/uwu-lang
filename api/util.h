#ifndef _API_UTIL_H_
#define _API_UTIL_H_

#include "vm.h"

UwUVMValue uwuutil_is_type(const char *fnname, UwUVMArgs *args, UwUVMType *type);
void uwuutil_require_min  (const char *fnname, UwUVMArgs *args, size_t n);
void uwuutil_require_max  (const char *fnname, UwUVMArgs *args, size_t n);
void uwuutil_require_exact(const char *fnname, UwUVMArgs *args, size_t n);
void uwuutil_require_none (const char *fnname, UwUVMArgs *args);

#endif

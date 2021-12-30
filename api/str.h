#ifndef _API_STR_H_
#define _API_STR_H_

#include "vm.h"

UwUVMValue uwustr_create(const char *value);
char *uwustr_get(UwUVMValue vm_value);

#endif

#ifndef _API_INT_H_
#define _API_INT_H_

#include "vm.h"

extern UwUVMType uwuint_type;
UwUVMValue       uwuint_create(int value);
int              uwuint_get(UwUVMValue vm_value);

#endif

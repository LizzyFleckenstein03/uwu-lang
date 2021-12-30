#ifndef _API_BOOL_H_
#define _API_BOOL_H_

#include <stdbool.h>
#include "vm.h"

extern UwUVMType uwubool_type;
UwUVMValue       uwubool_create(bool value);
bool             uwubool_get(UwUVMValue vm_value);

#endif
